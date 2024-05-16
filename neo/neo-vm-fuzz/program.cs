/*
 * neo-vm/tests/Neo.VM.Tests/UtScript.cs
 * neo-vm/tests/Neo.VM.Tests/UtDebugger.cs
 */

using Neo.VM;
using System;
using System.IO;
using System.Text;
using SharpFuzz;

namespace Neo.VM.Fuzz
{
    public static class Program
    {
        public static void Main(string[] args)
        {
            Fuzzer.OutOfProcess.Run(stream =>
            {
                try
                {
                    byte[] bytes = System.Text.Encoding.Default.GetBytes(stream);
                    var script = new Script(bytes);

                    using ExecutionEngine engine = new();
                    engine.LoadScript(script);
                    engine.Execute();
                }
                catch (...) { }
            });
        }
    }
}
