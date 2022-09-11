from selenium import webdriver
from selenium.webdriver.common.by import By
import os
from selenium.webdriver.support.select import Select


class ContactPage:
    name_input = (By.ID, 'name')
    surname_input = (By.ID, 'surname')
    mail_input = (By.ID, 'email')
    message_input = (By.ID, 'message')
    submit_form = (By.ID, 'contact_form')

    def __init__(self, browser):
        self.driver = browser
        self.URL = r"file://" + os.getcwd() + r"/page/index.html"
        self.driver.get(self.URL)
        self.driver.find_element_by_link_text('Contact').click()

    def take_screenshot(self, relative_path):
        self.driver.save_screenshot(relative_path)

    def test_form(self, name, surname, mail, country, message, screenshot_relative_path):
        self.driver.find_element(*self.name_input).send_keys(name)
        self.driver.find_element(*self.surname_input).send_keys(surname)
        self.driver.find_element(*self.mail_input).send_keys(mail)

        drop_country = Select(self.driver.find_element_by_id('country'))
        drop_country.select_by_visible_text(country)

        self.driver.find_element(*self.message_input).send_keys(message)
        self.driver.implicitly_wait(2)
        self.take_screenshot(screenshot_relative_path)
        self.driver.find_element(*self.submit_form).submit()
        self.driver.switch_to.alert.accept()
        self.driver.implicitly_wait(2)


driver = webdriver.Chrome(executable_path=r"./chromedriver")
# driver = webdriver.Firefox(executable_path=r"./geckodriver")
driver.implicitly_wait(5)
pageObject = ContactPage(driver)
pageObject.test_form(name='Krzysztof', surname="Jarzyna", mail="test@mail_provider.com", country="Poland", message="Hello World", screenshot_relative_path="zadanie6.png")
driver.quit()