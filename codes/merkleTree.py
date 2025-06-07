import hashlib


def sha256(data):
    return hashlib.sha256(data.encode('utf-8')).hexdigest()

def build_merkle_root(data_blocks):
    hashes = [sha256(block) for block in data_blocks]

    print("Leaf Hashes:")
    for h in hashes:
        print(h)

    while len(hashes) > 1:
        temp = []
        for i in range(0, len(hashes), 2):
            left = hashes[i]
            right = hashes[i+1] if i+1 < len(hashes) else left 
            combined = sha256(left + right)
            temp.append(combined)
        hashes = temp

    return hashes[0]

if __name__ == "__main__":
    data = ["Chunk A", "Chunk B", "Chunk C", "Chunk D"]
    root = build_merkle_root(data)
    print("\nMerkle Root:", root)
