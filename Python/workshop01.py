def native_string_matcher(text: str, pattern: str):
    n = len(text)
    m = len(pattern)
    
    found_indices = []
    
    if m == 0 or n == 0 or m > n:
        return found_indices

    for s in range(n - m + 1):
        is_match = True
        
        for i in range(m):
            if text[s + i] != pattern[i]:
                is_match = False
                break

        if is_match:
            found_indices.append(s)

    return found_indices


# take input from the user
text = input("Enter the text: ")
pattern = input("Enter the pattern: ")
result = native_string_matcher(text, pattern)
print("Pattern found at indices:", result)