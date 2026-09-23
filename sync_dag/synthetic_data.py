import numpy as np
import pandas as pd

# Number of contracts
N = 10000

np.random.seed(42)

# Generate realistic market parameters
spot_prices = np.random.uniform(50.0, 500.0, N)
# Strike prices roughly +/- 20% around spot
strike_prices = spot_prices * np.random.uniform(0.8, 1.2, N)
time_to_maturity = np.random.uniform(0.05, 2.0, N)  # in years (~2 weeks to 2 years)
risk_free_rate = np.random.uniform(0.01, 0.07, N)   # 1% to 7%
volatility = np.random.uniform(0.10, 0.60, N)       # 10% to 60% implied volatility

df = pd.DataFrame({
    'Spot': np.round(spot_prices, 2),
    'Strike': np.round(strike_prices, 2),
    'Time': np.round(time_to_maturity, 4),
    'Rate': np.round(risk_free_rate, 4),
    'Volatility': np.round(volatility, 4)
})

df.to_csv('market_data.csv', index=False)
print("Generated market_data.csv with 10,000 rows.")