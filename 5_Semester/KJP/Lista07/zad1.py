# !!!!!!!!!!!!
# NOT FINISHED
# !!!!!!!!!!!!

from bs4 import BeautifulSoup
from bs4.element import Comment
import urllib.request
import urllib.error
import re

# idea :
# get start_page & perform action on it
# if distance > 0 -> recursively call with (distance-1) for all links
# - use BFS for easier yielding
# - keep a set of url's and check if we already used it before recursive step


def get_soup_page(url):
    """
    Converts to soup, handles common errors
    :param url: path to webpage starting with 'https://
    :return: soup object representing the page
    """
    try:
        page = urllib.request.urlopen(url)
    except urllib.error.HTTPError as e:
        print(f'HTTP error: {e.code}')
        return None
    except urllib.error.URLError as e:
        print(f"URL - error: {e.reason}")
        return None
    return BeautifulSoup(markup=page, features="html.parser")


def get_links(soup_page):
    """
    :param soup_page: BeautifulSoup page object
    :return: list of links from current page
    """
    if soup_page is None:  # dead links
        return []

    regex = re.compile(r"^https?://")  # we don't want to follow relative links/anchors
    links = soup_page.findAll('a', attrs={'href': regex})
    return [link.get('href') for link in links]


def crawl(start_page, distance, payp):
    """
    :param start_page: url to starting page
    :param distance: max-depth of search, (0 - search only on current site)
    :param action: function that accepts a soup page and returns some value
    :return: an iterator of crawled pages and action performed on them [(url, action), ...]
    """
    visited_sites = set()  # set of url's

    bfs_q = [(start_page, distance)]  # sites left to visit

    # visit sites using breadth-first-search
    while bfs_q:
        cur_url, cur_dist = bfs_q.pop(0)

        if cur_url not in visited_sites:
            soup_page = get_soup_page(cur_url)

            visited_sites.add(cur_url)        # add to visited
            if soup_page is None:
                continue

            yield cur_url, action(soup_page)  # yield result

            if cur_dist >= 1:                 # if we can follow links
                for url in get_links(soup_page):
                    bfs_q.append((url, cur_dist - 1))


# https://stackoverflow.com/questions/1936466/beautifulsoup-grab-visible-webpage-text
def tag_visible(el):
    """
    :param el: webpage element
    :return: boolean value encoding if tag is visible to the user of webpage
    """
    if el.parent.name in ['script', 'style', 'head', 'title', 'meta', '[document]']:
        return False
    if isinstance(el, Comment):
        return False
    return True


def find_word_usage(word):
    """
    :param word: word to search for
    :return: function which gets a page and returns all visible sentences containing the word on a given page
    """
    def action(page):
        visible_texts = filter(tag_visible, page.find_all(text=True))

        # parsing the page
        # complicated because of usage of some of the tags
        sentences = []
        current = ""
        for string in visible_texts:
            if string == '':
                continue

            if string[-1] == '\n':
                if current == "" or current == "\n":
                    current = ""
                    continue
                elif current[-1] == '.':
                    sentences += [current]
                    current = ""
                    continue
                else:
                    continue

            # check if currently created sentence doesn't contain more sentences
            sentences_l = [s for s in current.split('.') if s]
            if len(sentences_l) > 1:

                sentences += [s + '.' for s in sentences_l[0:-1]]  # add the dot "back"
                current = sentences_l[-1]

            if string[-1] == '.':
                sentences += [current]
                current = ""

            # don't concatenate unrelated lines.
            if current != '' and (current[-1] != " " and string[0] != " "):
                current = ""
                continue

            current += string
        sentences += [current]  # to not mist last loop

        # match proper sentence form
        sentence_re = re.compile(r"([A-Z][^.\\\[!?]*[.!?])")
        proper_sentences = filter(sentence_re.match, sentences)

        # check for given keyword in sentence
        return {s.encode() for s in proper_sentences if (word + ' ' in s) or (' ' + word in s)}

    return action


# tests

# str1 = "Python in a sentence!"
# str2 = "another Python test"
# str3 = "A proper Python sentence."
# str4 = 'Proper sentence.'
#
# sentence_rex = re.compile(r"([A-Z][^.\\\[!?]*[.!?])$")
#
# print(sentence_rex.match(str1))
# print(sentence_rex.match(str2))
# print(sentence_rex.match(str3))
# print(sentence_rex.match(str4))

path = r"https://en.wikipedia.org/wiki/Python_(programming_language)"
for i in crawl(path, 1, find_word_usage("Python")):
    print(i)

# > time python3 zad1.py
#
#
