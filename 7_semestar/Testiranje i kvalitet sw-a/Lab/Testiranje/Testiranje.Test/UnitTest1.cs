namespace Testiranje.Test;

[TestFixture]
public class Tests
{
    [SetUp]
    public void Setup()
    {
        Console.WriteLine("Setup");
    }

    [Test]
    [TestCase(1, TestName = "Prvi prosti broj")]
    public void Test1(int broj)
    {
        Console.WriteLine($"{broj}-ti prosti broj.");
        Assert.That(Numbers.NthPrimeNumber(broj), Is.EqualTo(2));
    }

    [Test]
    [TestCase(5, TestName = "Peti prosti broj")]
    [TestCase(10, TestName = "Deseti prosti broj")]
    [TestCase(12, TestName = "Dvanaesti prosti broj")]
    public void Test2(int broj)
    {
        Console.WriteLine($"{broj}-ti prosti broj.");

        int nth = Numbers.FindNPrimeNumbers(broj).Last();

        Assert.That(Numbers.NthPrimeNumber(broj), Is.EqualTo(nth));
    }

    [Test]
    [TestCase(5, ExpectedResult = 11, TestName = "Peti prosti broj, expected.")]
    [TestCase(10, ExpectedResult = 29, TestName = "Deseti prosti broj, expected.")]
    [TestCase(12, ExpectedResult = 37, TestName = "Dvanaesti prosti broj, expected.")]
    public int Test3(int broj)
    {
        Console.WriteLine($"{broj}-ti prosti broj.");
        return Numbers.NthPrimeNumber(broj);
    }

    [Ignore("Ignorisan bez razloga")]
    [TestCase(TestName = "Ignorisan test")]
    public void Test4()
    {

    }

    [Test]
    public void Test5([Values(1, 2, 3)] int broj, [Range(0, 1, 0.5)] double doubleBroj)
    {
        Console.WriteLine($"Broj: {broj}, doubleBroj: {doubleBroj}");
        Assert.Multiple(() =>
        {
            Assert.That(typeof(int), Is.EqualTo(broj.GetType()));
            Assert.That(typeof(double), Is.EqualTo(doubleBroj.GetType()));
        });
    }

    [Test]
    [Timeout(1)]
    public void Test6()
    {
        var a = Numbers.FindPrimeNumbersLowerThanN(int.MaxValue).ToList();
        Assert.That(a.Count, Is.GreaterThan(0));
    }

    [Test]
    public void Test7()
    {
        Assert.Throws(typeof(ArgumentException), () =>
        {
            Numbers.FindPrimeNumbersLowerThanN(0).ToList();
        });
    }

    [TearDown]
    public void TearDown()
    {
        // Bolja varijanta je Disposable
        Console.WriteLine("Tear down");
    }
}
