import os
import psutil
from urllib.request import urlretrieve

from selenium import webdriver
from selenium.webdriver.chrome.options import Options


# 1
# from selenium.webdriver.firefox.options import Options
# firefox_options = Options()
# firefox_options.headless = True
# driver = webdriver.Firefox(options=firefox_options, executable_path=r"./geckodriver")
chrome_options = Options()
chrome_options.add_argument("--disable-extensions")
chrome_options.add_argument("--disable-gpu")
chrome_options.add_argument("--no-sandbox") # linux only
chrome_options.add_argument("--headless")
driver = webdriver.Chrome(options=chrome_options, executable_path=r"./chromedriver")

# 2
indexPath = r"file://" + os.getcwd() + r"/page/index.html"
driver.get(indexPath)
# 3
driver.find_element_by_link_text('Gallery').click()
# 4
os.makedirs('downloaded_images', exist_ok=True)

images = driver.find_elements_by_class_name('gallery')

for image in images:
    src = image.get_attribute('src')
    fileName = os.path.basename(src)
    urlretrieve(url=src, filename="downloaded_images/"+fileName)

driver.implicitly_wait(3)
# Close.
# u mnie potrzebowałem tego bo driver.quit ani driver.close nie działał
driver.quit()