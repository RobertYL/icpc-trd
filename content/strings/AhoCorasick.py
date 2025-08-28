/**
 * Author: Wilbert Chu
 * Description: None
 */
trie = [[0] * 26]
def insert(s):
    cur = 0
    for c in s:
        x = ord(c) - ord("A")
        if not trie[cur][x]:
            trie[cur][x] = len(trie)
            trie.append([0] * 26)
        cur = trie[cur][x]
    return cur
# insert all the strings here first
queue = [0]
fail = [0] * len(trie)
fail[0] = -1
for i in range(len(trie)):
    c = queue[i]
    for x in range(26):
        if not trie[c][x]:
            continue
        p = fail[c]
        while p > -1:
            if trie[p][x]:
                fail[trie[c][x]] = trie[p][x]
                break
            p = fail[p]
        queue.append(trie[c][x])
fail[0] = 0
go = [[0] * 26 for _ in range(len(trie))]
for c in queue:
    for x in range(26):
        go[c][x] = trie[c][x] if trie[c][x] else go[fail[c]][x]
