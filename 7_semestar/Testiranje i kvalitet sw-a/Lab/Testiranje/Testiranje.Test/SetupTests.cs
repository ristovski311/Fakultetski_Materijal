namespace Testiranje.Test;

[SetUpFixture]
public class SetupTests
{
    [OneTimeSetUp]
    public void RunBeforeAnyTests()
    {
        Console.WriteLine("Test setup...");
    }

    [OneTimeTearDown]
    public void RunAfterAnyTests()
    {
        Console.WriteLine("Test teardown...");
    }
}
