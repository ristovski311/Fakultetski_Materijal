using System.Text;

namespace restorani;

public static class Extensions
{
    public static string ToExceptionString(this Exception e)
    {
        StringBuilder sb = new();
        Exception? temp = e;
        int indent = 0;

        while (temp != null)
        {
            sb.AppendLine($"{new string(' ', indent)}{(indent == 0 ? "" : "-> ")}{temp.Message}");
            indent += 2;
            temp = temp.InnerException;
        }

        return sb.ToString();
    }
}