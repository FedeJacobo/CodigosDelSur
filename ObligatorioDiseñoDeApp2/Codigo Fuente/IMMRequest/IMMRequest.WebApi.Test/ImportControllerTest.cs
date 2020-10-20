using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.IDataImporter;
using IMMRequest.WebApi.Controllers;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.WebApi.Test
{
    [TestClass]
    public class ImportControllerTest
    {
        private IWebApiMapper webApiMapper;
        private Mock<IAreaLogic> areaLogic;
        private Mock<ITopicLogic> topicLogic;
        private Mock<ITypeReqLogic> typeLogic;
        private Mock<IImportLogic> importLogic;
        private ImportController importController;
        private readonly IConfiguration configuration;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            areaLogic = new Mock<IAreaLogic>();
            topicLogic = new Mock<ITopicLogic>();
            typeLogic = new Mock<ITypeReqLogic>();
            importLogic = new Mock<IImportLogic>();
            importController = new ImportController(importLogic.Object, webApiMapper, configuration);
        }

        [TestMethod]
        public void GetTypeParameterTest()
        {
            ICollection<string> parameterNames = new List<string>() { "parameterOne", "parameterTwo", "parameterThree" };
            string importer = "importer";
            importLogic.Setup(i => i.GetParameterNames(importer)).Returns(parameterNames);

            var result = importController.GetParameterNamesFromImporter(importer);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as ICollection<string>;

            importLogic.VerifyAll();

            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(parameterNames.Count, resultModelOut.Count);
        }

        [TestMethod]
        public void ImportDataTest()
        {
            ICollection<ParameterModelIn> parametersModelIn = new List<ParameterModelIn>() {
                new ParameterModelIn() { Name = "parameterOne", Value = "value1" },
                new ParameterModelIn() { Name = "parameterTwo", Value = "value2" },
                new ParameterModelIn() { Name = "parameterThree", Value = "value3" } };
            var importer = "importer";

            importLogic.Setup(i => i.ImportEverything(importer, It.IsAny<ICollection<Parameter>>())).Verifiable();

            var importModelIn = new ImportModelIn()
            {
                Name = importer,
                Parameters = parametersModelIn
            };

            var result = importController.Import(importModelIn);
            var createdResult = result as OkResult;

            importLogic.VerifyAll();
            Assert.IsNotNull(result);
        }
    }
}
