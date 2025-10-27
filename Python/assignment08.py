def fractional_knapsack(weights, profits, capacity):
    n = len(weights)
    ratio = []

    # Calculate profit-to-weight ratio for each parcel
    for i in range(n):
        ratio.append((profits[i] / weights[i], weights[i], profits[i]))

    # Sort by ratio (high to low)
    ratio.sort(reverse=True)

    total_profit = 0
    for r, w, p in ratio:
        if capacity == 0:
            break
        if w <= capacity:
            total_profit += p
            capacity -= w
        else:
            total_profit += r * capacity  # take fraction
            capacity = 0

    return total_profit


# ---- Main program ----
n = int(input("Enter number of parcels: "))

weights = []
profits = []

for i in range(n):
    w = float(input(f"Enter weight of parcel {i+1}: "))
    p = float(input(f"Enter profit of parcel {i+1}: "))
    weights.append(w)
    profits.append(p)

capacity = float(input("Enter truck capacity: "))

max_profit = fractional_knapsack(weights, profits, capacity)
print("\nMaximum Profit:", max_profit)
