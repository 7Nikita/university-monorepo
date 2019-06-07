def insert_sort(nums):
    for j in range(1, len(nums)):
        key = nums[j]
        i = j - 1
        while nums[j] > i > -1:
            nums[i + 1] = nums[i]
            i -= 1
        nums[i + 1] = key
    return nums


def merge_lists(left_sublist, right_sublist):
    i, j = 0, 0
    result = []
    while i < len(left_sublist) and j < len(right_sublist):
        if left_sublist[i] <= right_sublist[j]:
            result.append(left_sublist[i])
            i += 1
        else:
            result.append(right_sublist[j])
            j += 1
    result += left_sublist[i:]
    result += right_sublist[j:]
    return result


def merge_sort(nums):
    if len(nums) <= 1:
        return nums
    middle = int(len(nums) / 2)
    left_sublist = merge_sort(nums[:middle])
    right_sublist = merge_sort(nums[middle:])
    return merge_lists(left_sublist, right_sublist)


def quick_sort(x):
    if len(x) == 1 or len(x) == 0:
        return x
    else:
        pivot = x[0]
        i = 0
        for j in range(len(x)-1):
            if x[j + 1] < pivot:
                x[j + 1], x[i + 1] = x[i + 1], x[j + 1]
                i += 1
        x[0], x[i] = x[i], x[0]
        first_part = quick_sort(x[:i])
        second_part = quick_sort(x[i+1:])
        first_part.append(x[i])
        return first_part + second_part


def radix_sort(lst, radix=10):
    max_len = 32
    for x in range(max_len):
        bins = [[] for i in range(radix)]
        for y in lst:
            bins[(y / 10 ** x) % radix].append(y)
        lst = []
        for section in bins:
            lst.extend(section)
    return lst