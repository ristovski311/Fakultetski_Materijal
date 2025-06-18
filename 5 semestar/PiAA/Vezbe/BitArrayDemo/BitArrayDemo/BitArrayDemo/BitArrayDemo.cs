using System;
using System.Collections;
using System.Diagnostics;
public static class SamplesBitArray
{

    public static void Main()
    {

        // Creates and initializes several BitArrays.
        BitArray myBA1 = new BitArray(5);

        BitArray myBA2 = new BitArray(5, false);

        byte[] myBytes = new byte[5] { 1, 2, 3, 4, 5 };
        BitArray myBA3 = new BitArray(myBytes);

        bool[] myBools = new bool[5] { true, false, true, true, false };
        BitArray myBA4 = new BitArray(myBools);

        int[] myInts = new int[5] { 6, 7, 8, 9, 10 };
        BitArray myBA5 = new BitArray(myInts);

        // Displays the properties and values of the BitArrays.
        Console.WriteLine("myBA1");
        Console.WriteLine("   Count:    {0}", myBA1.Count);
        Console.WriteLine("   Length:   {0}", myBA1.Length);
        Console.WriteLine("   Values:");
        PrintValues(myBA1, 8);

        Console.WriteLine("myBA2");
        Console.WriteLine("   Count:    {0}", myBA2.Count);
        Console.WriteLine("   Length:   {0}", myBA2.Length);
        Console.WriteLine("   Values:");
        PrintValues(myBA2, 8);

        Console.WriteLine("myBA3");
        Console.WriteLine("   Count:    {0}", myBA3.Count);
        Console.WriteLine("   Length:   {0}", myBA3.Length);
        Console.WriteLine("   Values:");
        PrintValues(myBA3, 8);

        Console.WriteLine("myBA4");
        Console.WriteLine("   Count:    {0}", myBA4.Count);
        Console.WriteLine("   Length:   {0}", myBA4.Length);
        Console.WriteLine("   Values:");
        PrintValues(myBA4, 8);

        Console.WriteLine("myBA5");
        Console.WriteLine("   Count:    {0}", myBA5.Count);
        Console.WriteLine("   Length:   {0}", myBA5.Length);
        Console.WriteLine("   Values:");
        PrintValues(myBA5, 8);

        FromArray();

        DisplayBitArray();

        PerformanceTest();

        
    }

    public static void PrintValues(IEnumerable myList, int myWidth)
    {
        int i = myWidth;
        foreach (Object obj in myList)
        {
            if (i <= 0)
            {
                i = myWidth;
                Console.WriteLine();
            }
            i--;
            Console.Write("{0,8}", obj);
        }
        Console.WriteLine();
    }

    static void FromArray()
    {
        // Create BitArray from the array.
        BitArray bitArray = new BitArray(32);

        // Set three bits to 1.
        bitArray[3] = true;     // You can set the bits with the indexer.
        bitArray[5] = true;
        bitArray.Set(10, true); // You can set the bits with Set.

        // Count returns the total of all bits (1s and 0s).
        Console.WriteLine("--- Total bits ---");
        Console.WriteLine(bitArray.Count);

        // You can loop to count set bits.
        Console.WriteLine("--- Total bits set to 1 ---");
        Console.WriteLine(CountBitArray(bitArray));
    }

    /// <summary>
    /// Count set bits in BitArray.
    /// </summary>
    static int CountBitArray(BitArray bitArray)
    {
        int count = 0;
        foreach (bool bit in bitArray)
        {
            if (bit)
            {
                count++;
            }
        }
        return count;
    }

    static void DisplayBitArray()
    {
        //
        // Initialize BitArray with 4 true bits and 12 false bits.
        //
        BitArray bitArray1 = new BitArray(16);
        bitArray1.Set(0, true);
        bitArray1.Set(1, true);
        bitArray1.Set(4, true);
        bitArray1.Set(5, true);

        //
        // Display the BitArray.
        //
        DisplayBitArray(bitArray1);

        //
        // Initialize BitArray with two set bits.
        //
        BitArray bitArray2 = new BitArray(16);
        bitArray2.Set(0, true);
        bitArray2.Set(7, true);
        DisplayBitArray(bitArray2);

        //
        // And the bits.
        //
        bitArray1.And(bitArray2);
        DisplayBitArray(bitArray1);
    }

    /// <summary>
    /// Display bits as 0s and 1s.
    /// </summary>
    static void DisplayBitArray(BitArray bitArray)
    {
        for (int i = 0; i < bitArray.Count; i++)
        {
            bool bit = bitArray.Get(i);
            Console.Write(bit ? 1 : 0);
        }
        Console.WriteLine();
    }

    static void PerformanceTest()
    {
        Random r = new Random();
        r.Next(1000);

        const long N = 100000000;

        Console.WriteLine("Testing with {0} operations:", N);

        Console.WriteLine("   A UInt32 bitfield took {0} ms.", TestBitField(r, N));
        Console.WriteLine("   A BitArray (32) took {0} ms.", TestBitArray(r, N));
        Console.WriteLine("   A List<bool>(32) took {0} ms.", TestBoolArray(r, N));
        Console.WriteLine("   Append test took {0} ms.", AppendTest(r, N));
        Console.WriteLine("   Prepend test took {0} ms.", PrependTest(r, N));
        Console.WriteLine("   BitArrayToByteArray test took {0} ms.", BitArrayToByteArray(r, N));
        Console.WriteLine("   ToByteArray test took {0} ms.", ToByteArray(r, N));

        Console.Read();
    }


    static long TestBitField(Random r, long n)
    {
        UInt32 bitfield = 0;

        var sw = Stopwatch.StartNew();
        for (long i = 0; i < n; i++) {

            SetBit(ref bitfield, r.Next(32), true);
            bool b = GetBit(bitfield, r.Next(32));
            SetBit(ref bitfield, r.Next(32), b);
        }
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }

    static bool GetBit(UInt32 x, int bitnum) {
        if (bitnum < 0 || bitnum > 31)
            throw new ArgumentOutOfRangeException("Invalid bit number");

        return (x & (1 << bitnum)) != 0;
    }

    static void SetBit(ref UInt32 x, int bitnum, bool val)
    {
        if (bitnum < 0 || bitnum > 31)
            throw new ArgumentOutOfRangeException("Invalid bit number");

        if (val)
            x |= (UInt32)(1 << bitnum);
        else
            x &= ~(UInt32)(1 << bitnum);
    }



    static long TestBitArray(Random r, long n)
    {
        BitArray b = new BitArray(32, false);     // 40 bytes

        var sw = Stopwatch.StartNew();
        for (long i = 0; i < n; i++) {

            b.Set(r.Next(32), true);
            bool v = b.Get(r.Next(32));
            b.Set(r.Next(32), v);
        }
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }



    static long TestBoolArray(Random r, long n)
    {
        bool[] ba = new bool[32];

        var sw = Stopwatch.StartNew();
        for (long i = 0; i < n; i++) {

            ba[r.Next(32)] = true;
            bool v = ba[r.Next(32)];
            ba[r.Next(32)] = v;
        }
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }

    

    public static BitArray Prepend(this BitArray current, BitArray before)
    {
        var bools = new bool[current.Count + before.Count];
        before.CopyTo(bools, 0);
        current.CopyTo(bools, before.Count);
        return new BitArray(bools);
    }

    public static BitArray Append(this BitArray current, BitArray after)
    {
        var bools = new bool[current.Count + after.Count];
        current.CopyTo(bools, 0);
        after.CopyTo(bools, current.Count);
        return new BitArray(bools);
    }

    static long AppendTest(Random r, long n)
    {
        BitArray b = new BitArray((int)n, false);
        BitArray b2 = new BitArray((int)n, true);    

        var sw = Stopwatch.StartNew();
        BitArray c = b.Append(b2);
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }

    static long PrependTest(Random r, long n)
    {
        BitArray b = new BitArray((int)n, false);
        BitArray b2 = new BitArray((int)n, true);

        var sw = Stopwatch.StartNew();
        BitArray c = b.Prepend(b2);
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }

    static long BitArrayToByteArray(Random r, long n)
    {
        BitArray b = new BitArray((int)n, false);
        

        var sw = Stopwatch.StartNew();
        byte[] bts = BitArrayToByteArray(b);
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }

    public static byte[] BitArrayToByteArray(BitArray bits)
    {
        byte[] ret = new byte[(bits.Length - 1) / 8 + 1];
        bits.CopyTo(ret, 0);
        return ret;
    }

    static long ToByteArray(Random r, long n)
    {
        BitArray b = new BitArray((int)n, true);


        var sw = Stopwatch.StartNew();
        byte[] bts = b.ToByteArray();
        sw.Stop();
        return sw.ElapsedMilliseconds;
    }

    public static byte[] ToByteArray(this BitArray bits)
    {

        const int BYTE = 8;
        int length = (bits.Count / BYTE) + ((bits.Count % BYTE == 0) ? 0 : 1);
        var bytes = new byte[length];

        for (int i = 0; i < bits.Length; i++)
        {

            int bitIndex = i % BYTE;
            int byteIndex = i / BYTE;

            int mask = (bits[i] ? 1 : 0) << bitIndex;
            bytes[byteIndex] |= (byte)mask;

        }//for

        return bytes;

    }//ToByteArra

}