class XRange:
    def __init__(self, *args):
        if len(args) == 1:
            start, stop, step = 0, args[0], 1
        elif len(args) == 2:
            start, stop, step = args[0], args[1], 1
        elif len(args) == 3:
            start, stop, step = args
        else:
            raise TypeError(f'XRange expected at most 3 arguments, got {len(args)}')

        try:
            start, stop, step = int(start), int(stop), int(step)
        except ValueError:
            raise ValueError('XRange arguments expected to be integers')

        if step == 0:
            raise ValueError('XRange step argument expected not to be zero')
        elif step < 0:
            stop = min(stop, start)
        else:
            stop = max(stop, start)

        self._start = start
        self._stop = stop
        self._step = step
        self._len = (self._stop - self._start) // self._step + bool((self._stop - self._start) % self._step)

    def __len__(self):
        return self._len

    def __eq__(self, other):
        return isinstance(other, XRange) and \
               self._start == other._start and \
               self._stop == other._stop and \
               self._step == other._step

    def __iter__(self):
        cur = self._start
        while cur < self._stop:
            yield cur
            cur += self._step

    def __getitem__(self, item):
        if item < 0:
            item = self._len + item
        if item < 0 or item >= self._len:
            raise IndexError('XRange index is out of bounds')
        return self._start + item * self._step