import yfinance as yf
import sys
import pandas as pd
import matplotlib.pyplot as plt

def shortenNumber(number): #shortens numbers
    if number >= 1_000_000_000_000:
        return f"{number / 1_000_000_000_000:.1f}T"
    elif number >= 1_000_000_000:
        return f"{number / 1_000_000_000:.1f}B"
    elif number >= 1_000_000:
        return f"{number / 1_000_000:.1f}M"
    elif number >= 1_000:
        return f"{number / 1_000:.1f}K"
    else:
        return str(number)


def main():
    # Get arguments from C script
    if len(sys.argv) != 4:
        print("Error: Need symbol, period, and interval")
        return
    
    symbol = sys.argv[1]
    period = sys.argv[2]
    interval = sys.argv[3]
    
    try:
        # Fetch stock data
        stock = yf.Ticker(symbol)
        data = stock.history(period=period, interval=interval)
        
        if data.empty:
            print(f"No data found for {symbol}")
            return
        
       
        # Show basic info
        info = stock.info
        company = info.get('longName', 'N/A')
        marketCap = info.get('marketCap', 'N/A')
        currentPrice = info.get('currentPrice', 'N/A')
        
        # Create and show graph
        plt.figure(figsize=(12, 6))
        plt.plot(data.index, data['Close'], linewidth=2, color='blue')
        plt.title(f'{company} | Current Price: {currentPrice}\$ | Market Cap: {shortenNumber(marketCap)}\$')
        plt.xlabel('Date')
        plt.ylabel('Price ($)')
        plt.grid(True, alpha=0.3)
        plt.xticks(rotation=45)
        plt.tight_layout()
        plt.show()
        
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()