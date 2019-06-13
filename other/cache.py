
import cPickle


class Cache(object):
    def __init__(self, func):
        self.func = func
        self.cache_dict = {}

    def __call__(self, *args, **kwargs):
        hash_code = cPickle.dumps((args, sorted(kwargs.iteritems())))
        from_cache = True
        if hash_code not in self.cache_dict:
            self.cache_dict[hash_code] = self.func(*args, **kwargs)
            from_cache = False
        return self.cache_dict[hash_code], from_cache


def cached(func):
    cache = Cache(func)

    def on_call(*args, **kwargs):
        return cache(*args, **kwargs)
    return on_call

