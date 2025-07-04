import org.openqa.selenium.By;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

public class GoogleAuthApp {

    public static void main(String[] args) {
        String email = "lalka21058@gmail.com";
        String password = "Jon21058!";

        ChromeDriver driver = null;
        try {
            System.out.println("===== Начало процесса =====");
            AuthHelper.LoginResult result = AuthHelper.login(email, password);
            driver = result.driver;
            System.out.println("Успешный вход! Текущий URL: " + driver.getCurrentUrl());
            safeSleep(5000);

            // Переключение на iframe боковой панели
            switchToSidebarFrame(driver, result.wait);

            // Клик по кнопке "Новый контакт"
            clickNewContactButton(driver, result.wait);

            // Заполнение полей
            fillField(driver, result.wait, "//input[@aria-label='Имя']", "Даниил");
            fillField(driver, result.wait, "//input[@aria-label='Эл. почта']", "kulachdv@gmail.com");

            // Сохранение контакта
            clickSaveButton(driver, result.wait);

            // Демонстрация результата
            System.out.println("Демонстрация 15 секунд...");
            safeSleep(15000);
            System.out.println("===== Процесс завершен успешно =====");

        } catch (Exception e) {
            System.err.println("Ошибка: " + e.getMessage());
            e.printStackTrace();
            System.out.println("===== Процесс завершен с ошибками =====");
        } finally {
            if (driver != null) {
                driver.quit();
            }
        }
    }

    private static void switchToSidebarFrame(ChromeDriver driver, WebDriverWait wait) {
        By frameLocator = By.xpath("//iframe[contains(@class, 'brC-brG-avO') and contains(@title, 'Контакты')]");
        WebElement frameElement = wait.until(ExpectedConditions.presenceOfElementLocated(frameLocator));
        driver.switchTo().frame(frameElement);
        safeSleep(2000);
    }

    private static void clickNewContactButton(ChromeDriver driver, WebDriverWait wait) {
        By buttonLocator = By.xpath("//button[.//span[text()='Новый контакт' or text()='New contact']]");
        WebElement button = wait.until(ExpectedConditions.elementToBeClickable(buttonLocator));
        scrollToElement(driver, button);
        safeSleep(1000);
        jsClick(driver, button);
        wait.until(ExpectedConditions.visibilityOfElementLocated(By.xpath("//input[@aria-label='Имя']")));
    }

    private static void fillField(ChromeDriver driver, WebDriverWait wait, String xpath, String value) {
        By locator = By.xpath(xpath);
        WebElement field = wait.until(ExpectedConditions.visibilityOfElementLocated(locator));
        scrollToElement(driver, field);
        safeSleep(500);
        jsClick(driver, field);
        safeSleep(500);
        field.clear();
        safeSleep(200);
        field.sendKeys(value);
        safeSleep(1000);

        // Проверка введенного значения
        String actualValue = field.getAttribute("value");
        if (!value.equals(actualValue)) {
            throw new RuntimeException("Значение не введено в поле. Ожидалось: '" + value + "', получено: '" + actualValue + "'");
        }
    }

    private static void clickSaveButton(ChromeDriver driver, WebDriverWait wait) {
        By saveButtonLocator = By.xpath("//button[@aria-label='Сохранить']");
        WebElement saveButton = wait.until(ExpectedConditions.elementToBeClickable(saveButtonLocator));
        scrollToElement(driver, saveButton);
        safeSleep(500);
        jsClick(driver, saveButton);
        wait.until(ExpectedConditions.visibilityOfElementLocated(By.xpath("//div[contains(text(),'Сохранено')]")));
        safeSleep(3000);
    }

    private static void scrollToElement(ChromeDriver driver, WebElement element) {
        ((JavascriptExecutor) driver).executeScript(
                "arguments[0].scrollIntoView({behavior: 'smooth', block: 'center', inline: 'center'});",
                element
        );
        safeSleep(500);
    }

    private static void jsClick(ChromeDriver driver, WebElement element) {
        ((JavascriptExecutor) driver).executeScript("arguments[0].click();", element);
        safeSleep(500);
    }

    private static void safeSleep(long millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}