using Neo.IO;
using Neo.Json;
using Neo.Network.P2P.Payloads;
using System;
using System.IO;
using Neo.SmartContract;
using Neo.SmartContract.Manifest;
using SharpFuzz;

namespace Neo.Fuzz
{
    public static class Program
    {
        public static void Main(string[] args)
        {
            Fuzzer.OutOfProcess.Run(stream =>
            {

                byte[] byteArray = System.Text.Encoding.UTF8.GetBytes(stream);

                if (byteArray.Length < 10 || byteArray.Length > 1024)
                {
                    return;
                }

                try
                {
                    var manifest = ContractManifest.Parse(stream);
                }
                catch (...) { }
            });
        }
    }
}

