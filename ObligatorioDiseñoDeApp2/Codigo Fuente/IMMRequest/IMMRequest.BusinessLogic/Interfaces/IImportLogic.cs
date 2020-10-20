using IMMRequest.IDataImporter;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic.Interfaces
{
    public interface IImportLogic
    {
        Tuple<int, int>[] ImportEverything(string importer, ICollection<Parameter> parameters);
        ICollection<string> GetParameterNames(string importer);
    }
}
