using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace IMMRequest.BusinessLogic
{
    public class ImportLogic : IImportLogic
    {
        private readonly IRepository<AreaEntity> areaRepository;
        private readonly IRepository<TopicEntity> topicRepository;
        private readonly IRepository<TypeReqEntity> typeRepository;
        private IUnitOfWork unitOfWork;
        private readonly IConfiguration configuration;
        private IAreaLogic areaLogic;
        private ITopicLogic topicLogic;
        private ITypeReqLogic typeLogic;

        public ImportLogic(IUnitOfWork unitOfWork, IConfiguration configuration, IAreaLogic areaLogic, ITopicLogic topicLogic, ITypeReqLogic typeLogic)
        {
            this.unitOfWork = unitOfWork;
            this.areaRepository = unitOfWork.AreaRepository;
            this.topicRepository = unitOfWork.TopicRepository;
            this.typeRepository = unitOfWork.TypeReqRepository;
            this.configuration = configuration;
            this.areaLogic = areaLogic;
            this.topicLogic = topicLogic;
            this.typeLogic = typeLogic;
        }

        public Tuple<int, int>[] ImportEverything(string importer, ICollection<Parameter> parameters)
        {
            Tuple<int, int>[] result = new Tuple<int, int>[3];
            IGenericImporter genericInterface;
            genericInterface = generateDataWithImporter(importer);
            importAreas(parameters, ref result, genericInterface);
            importTopics(parameters, ref result, genericInterface);
            importTypes(parameters, ref result, genericInterface);
            return result;
        }

        public ICollection<string> GetParameterNames(string importer)
        {
            IGenericImporter genericInterface;
            try
            {
                genericInterface = this.CreateInterface(importer);
            }
            catch (FileNotFoundException)
            {
                throw new ArgumentException($"File not found, please verify there is a valid generator in Assemblies/{importer} with name: {importer}");
            }
            catch (InvalidOperationException)
            {
                throw new ArgumentException("This data generator does not implement IGenericInterface correctly");
            }
            return genericInterface.GetTypeParameters();
        }

        private void importAreas(ICollection<Parameter> parameters, ref Tuple<int, int>[] result, IGenericImporter genericInterface)
        {
            try
            {
                string test = genericInterface.GetName();
                List<AreaEntity> importedAreas = genericInterface.GetAreas(parameters).ToList();
                int totalAreas = importedAreas.Count;
                int succesfulAreas = 0;

                foreach (AreaEntity importedArea in importedAreas)
                {
                    try
                    {
                        areaLogic.Add(importedArea);
                        succesfulAreas++;
                    }
                    catch (ArgumentException e) 
                    {
                        throw new ArgumentException(e.Message);
                    }
                }
                result[0] = new Tuple<int, int>(totalAreas, succesfulAreas);
            }
            catch (ArgumentException e)
            {
                throw new ArgumentException(e.Message);
            }
        }

        private void importTopics(ICollection<Parameter> parameters, ref Tuple<int, int>[] result, IGenericImporter genericInterface)
        {
            try
            {
                ICollection<TopicEntity> importedTopicsCollection = genericInterface.GetTopics(parameters);
                List<TopicEntity> importedTopics = importedTopicsCollection.ToList();
                int totalTopics = importedTopics.Count;
                int succesfulTopics = 0;

                foreach (TopicEntity importedTopic in importedTopics)
                {
                    try
                    {
                        topicLogic.Add(importedTopic);
                        succesfulTopics++;
                    }
                    catch (ArgumentException) { }
                }
                result[1] = new Tuple<int, int>(totalTopics, succesfulTopics);
            }
            catch (ArgumentException e)
            {
                throw new ArgumentException(e.Message);
            }
        }

        private void importTypes(ICollection<Parameter> parameters, ref Tuple<int, int>[] result, IGenericImporter genericInterface)
        {
            try
            {
                ICollection<TypeReqEntity> importedTypesCollection = genericInterface.GetTypeReqs(parameters);
                List<TypeReqEntity> importedTypes = importedTypesCollection.ToList();
                int totalTypes = importedTypes.Count;
                int succesfulTypes = 0;

                foreach (TypeReqEntity importedType in importedTypes)
                {
                    try
                    {
                        typeLogic.Add(importedType);
                        succesfulTypes++;
                    }
                    catch (ArgumentException) { }
                }
                result[2] = new Tuple<int, int>(totalTypes, succesfulTypes);
            }
            catch (ArgumentException e)
            {
                throw new ArgumentException(e.Message);
            }
        }

        private IGenericImporter generateDataWithImporter(string importer)
        {
            IGenericImporter genericInterface;
            try
            {
                genericInterface = this.CreateInterface(importer);
            }
            catch (FileNotFoundException)
            {
                throw new ArgumentException($"File not found, please verify there is a valid data generator in Assemblies/{importer} with name: {importer}");
            }
            catch (InvalidOperationException)
            {
                throw new ArgumentException("This data generator does not implement IGenericInterface correctly");
            }
            return genericInterface;
        }

        private IGenericImporter CreateInterface(string importer)
        {
            //string[] filesArray = Directory.GetFiles(@".\\Assemblies", "*.dll");
            //var path = "IMMRequest.WebApi.Assemblies\\";
            var path = @"Assemblies\\";
            var dllFile = new FileInfo(path + $@"IMMRequest.{importer}DataImporter.dll");
            Assembly myAssembly = Assembly.LoadFile(dllFile.FullName);
            List<Type> implementations = this.GetTypesInAssembly<IGenericImporter>(myAssembly);
            IGenericImporter genericInterface = (IGenericImporter) Activator.CreateInstance(implementations.First(), new object[] { });
            return genericInterface;
        }

        private List<Type> GetTypesInAssembly<T>(Assembly assembly)
        {
            List<Type> types = new List<Type>();
            foreach (var type in assembly.GetTypes())
            {
                if (typeof(IGenericImporter).IsAssignableFrom(type))
                    types.Add(type);
            }
            return types;
        }
    }
}

