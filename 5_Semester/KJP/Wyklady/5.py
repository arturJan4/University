#  parsing texts

# -------------------------------------------------------
# regex in Python
# * vs +
# () for grouping

import re
if re.match("brr+um", "brrrrrum!!!!"):
    print("match")

# match vs search
# match - prefix of string
# search - anywhere in the string

# returns match object or None

# compile regex if you use it a lot
# refer to string-matching algorithms (and how they build somewhat finite automata for given pattern)
automata = re.compile('brr+um')
res = automata.search('test brrrum')
print(res)
print(res.group())
print(res.start())

# example: find all links to other sites
# we assume some stuff for simplification

address = '([a-zA-Z]+.)*[a-zA-Z]+'
regex_cmpl = re.compile('http://' + address)

import urllib.request

host = "http://www.ii.uni.wroc.pl"

with urllib.request.urlopen(host) as f:
    text = f.read().decode('utf-8')

print([url.group() for url in regex_cmpl.finditer(text)])

# more symobls
# {m, n} -> at least m, at most n
# ? -> 0/1 appearance
# w1|w2 -> alternative
# . -> any symbol
# \d, \w, \Z -> digit, alphanumeric, end of text

# escaping for special char is easy
# but how to find '\['
re.match("\\\\\[", "[")
# how does it happen?
# first python converts it using escapes to `\\\[`
# then according to regex rules `\\` -> `\`, `\[` -> `[`
# we can use raw strings to cut down on processing steps

# grouping fragments of regex
res = re.match("a(b*)a.*(a)", "abbabbba")
print(res.groups())

# grouping expression
# (?P<name>regexp)

# example: get day/month/year from year
pattern = "(?P<year>\d{4})(?P<month>\d{2})(?P<day>\d{2})"
res = re.search(pattern, "in the date 20211116 there is sth")
print(res.group("year"), "-", res.group("month"), "-", res.group("day"))

# re.sub() example on slides (converting date format)
# re.sub(pattern, func, text) where func takes match object and returns string

# -------------------------------------------------------
# processing HTML
# HTML is a sequence of tags
# we have <stard> and </end> tags

# ---
# html.parser.HTMLParser
# has handlers for start/end tag and data, attributes
# class MyHTMLParser(html.parser.HTMLParser)
# myparser.feed(page)

# example: print all "href" links
import html.parser


class MyHTMLParser(html.parser.HTMLParser):
    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for (atr, val) in attr:
                if atr == 'href':
                    print(val)


my_parser = MyHTMLParser()

# with open('python.html') as data:
#   my_parser.feed(data)

# ---
# BeautifulSoup -> (not in standard :( )
# import bs4
# and we can access by '.' methods after parsing the page
# for example
# data.title.string
# data.title.parent.name

# example: list of links
# [link.get('href') for link in dane.find_all('a')]

# example: all links to thumbnails
# find all images where there is attribute that matches to the regex
# data.find_all('img', { 'src': re.compile('.*thumbnail.*') })

# -------------------------------------------------------
# XML parsing

# ---
# 1st strategy -> similar to above html.parser.HTMLParser
# xml.sax -> read-only, fast, but memory-heavy
# class handle.ContextHandler

# example: spreadsheet structure (both for .ods, and .xlsx) is .xml (content.xml)
# tip: read it using a browser (like firefox)
# implementing .ods parser for the spreadsheet
# zipfile lib usage -> unzipping "temporary in memory" & just using zf.open() for files inside

# 2nd strategy -> creating DOM (Document Object Model) tree representing XML
# Node object -> name, value, attributes, childNodes
# we can then parse node by node
# appending/removing/replacing children

# BeautifulSoup can also be used for xml parsing
