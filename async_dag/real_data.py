from datetime import datetime, timezone

import numpy as np
import pandas as pd
import yfinance as yf


ticker = yf.Ticker("SPY")
expirations = ticker.options

if not expirations:
    raise RuntimeError("No option expiration dates were returned.")

history = ticker.history(period="5d")

if history.empty or history["Close"].dropna().empty:
    raise RuntimeError("Could not obtain a valid SPY price.")

spot = float(history["Close"].dropna().iloc[-1])
today = datetime.now(timezone.utc).date()

all_calls = []

for expiration in expirations[:5]:
    option_chain = ticker.option_chain(expiration)
    calls = option_chain.calls.copy()

    expiration_date = datetime.strptime(
        expiration, "%Y-%m-%d"
    ).date()

    time_to_expiration = (
        expiration_date - today
    ).days / 365.0

    calls["Spot"] = spot
    calls["Time"] = time_to_expiration
    calls["Rate"] = 0.05
    calls["Volatility"] = calls["impliedVolatility"]

    all_calls.append(
        calls[
            ["Spot", "strike", "Time", "Rate", "Volatility"]
        ].rename(columns={"strike": "Strike"})
    )

if not all_calls:
    raise RuntimeError("No call-option data was returned.")

df = pd.concat(all_calls, ignore_index=True)

numeric_columns = [
    "Spot",
    "Strike",
    "Time",
    "Rate",
    "Volatility",
]

for column in numeric_columns:
    df[column] = pd.to_numeric(df[column], errors="coerce")

df = df.replace([np.inf, -np.inf], np.nan)
df = df.dropna(subset=numeric_columns)

df = df[
    (df["Spot"] > 0)
    & (df["Strike"] > 0)
    & (df["Time"] > 0)
    & (df["Volatility"] > 0)
]

if df.empty:
    raise RuntimeError("No valid option rows remain after cleaning.")

print("Rows written:", len(df))
print(df.isna().sum())
print(df.describe())

df.to_csv("market_data_real.csv", index=False)