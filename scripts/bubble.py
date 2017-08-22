'''
The data structure representing a Bubble.
'''
class Bubble:
    def __init__(self, bubble_num):
        self.num = bubble_num
        self.paths = {}

    def add_path(self, taxon, path):
        self.paths[taxon] = path

    def __str__(self):
        out = ''
        for taxon, path in self.paths.items():
            out += '> ' + taxon + '\n'
            out += str(path) + '\n'
        return out

    def to_expanded_str(self):
        out = ''
        inv_paths = {}
        for taxon, path in self.paths.items():
            inv_paths[path] = inv_paths.get(path, [])
            inv_paths[path].append(taxon)
        for path, taxa in inv_paths.items():
            out += '> bubble ' + str(self.num) + ' for ' + ', '.join(taxa) + '\n'
            out += str(path) + '\n'
        return out
