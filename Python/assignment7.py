
def merge_sort(orders):
    if len(orders) <= 1:
        return orders

    mid = len(orders) // 2
    left = merge_sort(orders[:mid])
    right = merge_sort(orders[mid:])

    return merge(left, right)


def merge(left, right):
    sorted_list = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i]["delivery_time"] <= right[j]["delivery_time"]:
            sorted_list.append(left[i])
            i += 1
        else:
            sorted_list.append(right[j])
            j += 1

    sorted_list.extend(left[i:])
    sorted_list.extend(right[j:])

    return sorted_list


# orders = [
#     {"id": 101, "customer": "Abhay", "delivery_time": 5},
#     {"id": 102, "customer": "Alan", "delivery_time": 2},
#     {"id": 103, "customer": "Aman", "delivery_time": 8},
#     {"id": 104, "customer": "aditya", "delivery_time": 1},
#     {"id": 105, "customer": "Pradeep", "delivery_time": 3},
# ]

orders = []
n = int(input("Enter number of orders: "))

for i in range(n):
    order_id = int(input(f"Enter Order ID for order {i+1}: "))
    customer = input(f"Enter Customer Name for order {i+1}: ")
    delivery_time = int(input(f"Enter Delivery Time for order {i+1}: "))
    orders.append({"id": order_id, "customer": customer, "delivery_time": delivery_time})

print("\nOriginal Orders:")
for order in orders:
    print(order)

sorted_orders = merge_sort(orders)

print("\nSorted Orders by Delivery Time:")
for order in sorted_orders:
    print(order)
