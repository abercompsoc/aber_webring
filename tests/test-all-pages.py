'''
A brute force method of testing all possible requests to the API
This should realistically be a set of unit tests that send one request
and make sure the response is a redirect and nothing else.

This can be implemented when the webring gets big enough to need that

USAGE:
python3 test-all-pages.py <page_to_test>
'''

import webbrowser
import csv
import sys

def open_in_browser(page):
    webbrowser.open(page)


if len(sys.argv) <= 1:
    print("Enter csv file of pages to test")
    exit(1)

file_path = sys.argv[1]
pages = None

with open(file_path) as file:
    pages = csv.reader(file)
    print(pages)
    for page in pages:
        open_in_browser(f"http://localhost:18080/{page[1]}/left")
        open_in_browser(f"http://localhost:18080/{page[1]}/right")
    
