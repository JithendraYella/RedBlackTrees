# RedBlackTrees
An event counter using red-black tree. Each event has two fields: ID and count, where count is the number of active events with the given ID. The event counter stores only those ID’s whose count is > 0. Once a count drops below 1, that ID is removed. Initially, the program builds a red-black tree from a sorted list of n events (i.e., n pairs (ID, count) in ascending order of ID) in O(n) time.The counter supports the following operations in the specified time complexity.

1. Increase(theID, m)

Desc: Increase the count of the event theID by m. If theID is not present, insert it. Print the count of theID after the addition.

Time Complexity: O(log n)

2. Reduce(theID, m)

Desc: Decrease the count of theID by m. If theID’s count becomes less than or equal to 0, remove theID from the counter. Print the count of theID after the deletion, or 0 if theID is removed or not present.

Time Complexity: O(log n)

3. Count(theID)

Desc: Print the count of theID. If not present, print 0.

Time Complexity:  O(log n)


4. InRange(ID1, ID2)

Desc: Print the total count for IDs between ID1 and ID2 inclusively. Note, ID1 ≤ ID2

Time Complexity: O(log n + s) where s is the number of IDs in the range.


5. Next(theID)
Desc: Print the ID and the count of the event with the lowest ID that is greater that theID. Print “0 0”, if there is no next ID.

Time Complexity: O(log n)


6. Previous(theID)

Desc: Print the ID and the count of the event with the greatest key that is less that theID. Print “0 0”, if there is no previous ID.

Time Complexity: O(log n)
