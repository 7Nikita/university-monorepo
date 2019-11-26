import re


def email_validator(address) -> bool:
    """email address validator"""
    pattern = re.compile(r'^[A-z]\w*@[A-z]\w*\.[A-z]+$')
    return True if re.match(pattern, address) is not None else False


def float_validator(number) -> bool:
    """float number validator"""
    pattern = re.compile(r'^\d+[\.,]\d+$')
    return True if re.match(pattern, number) is not None else False


def url_validator(url, group) -> str:
    pattern = re.compile(r'^((?P<scheme>[A-z]+):\/\/)?(?P<host>[\w\.]+)(:(?P<protocol>\d+))?(?P<path>[\w\/\.]+)?$')
    m = re.match(pattern, url)
    return m.group(group)

