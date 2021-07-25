import os
from selenium import webdriver
from selenium.webdriver.support.select import Select
# 1
# driver = webdriver.Firefox(executable_path=r"./geckodriver")
driver = webdriver.Chrome(executable_path=r"./chromedriver")
indexPath = r"file://" + os.getcwd() + r"/page/index.html"
driver.get(indexPath)
driver.implicitly_wait(1)
# 2
driver.find_element_by_link_text('Contact').click()
driver.implicitly_wait(1)
# 3
el = driver.find_element_by_id('name').send_keys('Jan')
driver.find_element_by_id('surname').send_keys('Kowalski')
driver.find_element_by_id('email').send_keys('testmail@gmail.com')

dropCountry = Select(driver.find_element_by_id('country'))
dropCountry.select_by_visible_text('Poland')

driver.find_element_by_id('message').send_keys('ex message')
driver.implicitly_wait(1)
# 4
driver.save_screenshot('zadanie1.png')
# 5
driver.find_element_by_id('contact_form').submit()
driver.implicitly_wait(1)
# 6
driver.switch_to.alert.accept()
driver.implicitly_wait(1)
# Close.
driver.quit()
