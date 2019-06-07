class Vector:
    def __init__(self, elements):
        if type(elements) is not list:
            raise TypeError('Vector argument expected to be list')
        self.values = elements
        self.len = len(elements)

    def __len__(self):
        return self.len

    def __str__(self):
        return 'Vector(' + ', '.join(str(i) for i in self.values) + ')'

    def __getitem__(self, item):
        if type(item) is not int:
            raise AttributeError()
        return self.values[item]

    def __eq__(self, other):
        return self.values == other.values

    def __add__(self, other):
        if self.len != other.len:
            raise AttributeError()
        return Vector([x + y for x, y in zip(self.values, other.values)])

    def __sub__(self, other):
        if self.len != other.len:
            raise AttributeError()
        return Vector([x - y for x, y in zip(self.values, other.values)])

    def __mul__(self, other):
        if isinstance(other, Vector):
            if other.len != self.len:
                raise AttributeError()
            return sum(x * y for x, y in zip(self.values, other.values))
        elif type(other) in (int, float):
            return Vector([x * other for x in self.values])
        else:
            raise AttributeError()

    def __rmul__(self, other):
        return self.__mul__(other)