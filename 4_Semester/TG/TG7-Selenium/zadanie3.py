from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.common.exceptions import TimeoutException
import time
# 1
# driver = webdriver.Firefox(executable_path=r"./geckodriver")
driver = webdriver.Chrome(executable_path=r"./chromedriver")
indexPath = r"https://en.wikipedia.org/"
driver.get(indexPath)

# 2
driver.find_element_by_id('searchInput').send_keys('python')
driver.find_element_by_id('searchButton').click()

# 3
current_window = driver.current_window_handle


# 4b
def find_first_paragraph():
    try:
        WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'firstHeading')))
    except TimeoutException:
        print("timeout - waiting for content")

    headers = driver.find_elements_by_id('firstHeading')

    if len(headers) == 0:  # page without a header
        return

    header = headers[0].text
    if (header == "Python") or ("Editing" in header):
        return

    print(header)  # title

    body = driver.find_elements_by_class_name('mw-parser-output')
    if len(body) > 0:
        all_paragraphs = body[0].find_elements_by_tag_name('p')
        non_empty_texts = [par.text for par in all_paragraphs if len(par.text) > 0]
        if len(non_empty_texts) == 0:
            return
        print(non_empty_texts[0], end='\n\n')  # first non-empty paragraph

    return


elements = driver.find_elements_by_xpath("//div[@class='mw-parser-output']//li//a")  # searches for links inside a result list
for elem in elements:
    href = str(elem.get_attribute('href'))
    if "Python" in href:
        # 4 a
        # open in new tab
        driver.execute_script('window.open(arguments[0]);', href)
        # get new window/tab ID
        new_window = [window for window in driver.window_handles if window != current_window][0]
        # switch to new window
        driver.switch_to.window(new_window)

        time.sleep(1)

        # 4b
        # if possible finds first paragraph and header and prints it
        find_first_paragraph()

        # 4c
        # close new window
        driver.close()
        # switch to initial window
        driver.switch_to.window(current_window)

# Close.
driver.quit()
