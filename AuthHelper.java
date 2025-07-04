// AuthHelper.java
import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import java.time.Duration;
import java.util.Collections;
import java.util.logging.Level;

public class AuthHelper {

    public static class LoginResult {
        public final ChromeDriver driver;
        public final WebDriverWait wait;

        public LoginResult(ChromeDriver driver, WebDriverWait wait) {
            this.driver = driver;
            this.wait = wait;
        }
    }

    public static LoginResult login(String email, String password) {
        WebDriverManager.chromedriver().setup();
        java.util.logging.Logger.getLogger("org.openqa.selenium").setLevel(Level.SEVERE);

        ChromeOptions options = new ChromeOptions();
        options.setExperimentalOption("excludeSwitches", Collections.singletonList("enable-automation"));
        options.setExperimentalOption("useAutomationExtension", false);
        options.addArguments(
                "--disable-blink-features=AutomationControlled",
                "--start-maximized",
                "--disable-notifications",
                "--disable-popup-blocking",
                "--no-sandbox",
                "--disable-dev-shm-usage",
                "--disable-gpu",
                "--lang=ru-RU"
        );

        ChromeDriver driver = new ChromeDriver(options);
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(30));

        try {
            driver.get("https://accounts.google.com/signin/v2/identifier?service=mail&flowName=GlifWebSignIn&flowEntry=ServiceLogin");

            // Ввод email
            WebElement emailField = wait.until(
                    ExpectedConditions.elementToBeClickable(By.id("identifierId"))
            );
            emailField.sendKeys(email);
            driver.findElement(By.id("identifierNext")).click();

            // Скрываем флаг автоматизации
            ((JavascriptExecutor) driver).executeScript(
                    "Object.defineProperty(navigator, 'webdriver', {get: () => undefined})"
            );

            // Ввод пароля
            WebElement passwordField = wait.until(
                    ExpectedConditions.elementToBeClickable(
                            By.cssSelector("input[type='password'][name='Passwd']")
                    )
            );
            passwordField.sendKeys(password);

            WebElement nextButton = wait.until(
                    ExpectedConditions.elementToBeClickable(By.id("passwordNext"))
            );
            nextButton.click();

            // Проверка успешного входа
            wait.until(ExpectedConditions.or(
                    ExpectedConditions.urlContains("mail.google.com"),
                    ExpectedConditions.urlContains("myaccount.google.com"),
                    ExpectedConditions.urlContains("inbox")
            ));

            // Закрытие всплывающего окна Chrome
            try {
                WebElement skipButton = new WebDriverWait(driver, Duration.ofSeconds(5))
                        .until(ExpectedConditions.elementToBeClickable(
                                By.xpath("//button[contains(., 'Использовать Chrome без входа в аккаунт')]")
                        ));
                ((JavascriptExecutor) driver).executeScript("arguments[0].click();", skipButton);
                System.out.println("Всплывающее окно Chrome закрыто");
            } catch (TimeoutException ignored) {
                System.out.println("Всплывающее окно не обнаружено");
            }

            return new LoginResult(driver, wait);

        } catch (Exception e) {
            System.err.println("Ошибка при входе: " + e.getMessage());
            driver.quit();
            throw new RuntimeException("Ошибка авторизации", e);
        }
    }
}