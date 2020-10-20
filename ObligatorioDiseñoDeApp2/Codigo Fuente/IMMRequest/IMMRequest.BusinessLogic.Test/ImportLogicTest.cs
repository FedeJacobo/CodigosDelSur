using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using Microsoft.Extensions.Configuration;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace IMMRequest.BusinessLogic.Test
{
    [TestClass]
    public class ImportLogicTest
    {
        private string importer;
        private ICollection<Parameter> parameters;
        private AreaEntity area;
        private TopicEntity topic;
        private TypeReqEntity type;
        private Mock<IUnitOfWork> unitOfWork;
        private Mock<IRepository<AreaEntity>> areaRepository;
        private Mock<IRepository<TopicEntity>> topicRepository;
        private Mock<IRepository<TypeReqEntity>> typeRepository;
        private IAreaLogic areaLogic;
        private ITopicLogic topicLogic;
        private ITypeReqLogic typeLogic;
        private ImportLogic importLogic;

        [TestInitialize]
        public void TestInitialize()
        {
            area = new AreaEntity
            {
                Id = 1,
                Name = "Limpieza",
                Topics = new List<TopicEntity>()
            };

            topic = new TopicEntity
            {
                Id = 1,
                Name = "Contenedores de basura",
                AreaEntityId = 1,
                RequestTypes = new List<TypeReqEntity>()
            };

            type = new TypeReqEntity
            {
                Id = 1,
                Name = "Roto",
                AdditionalFields = new List<AdditionalFieldEntity>(),
                TopicEntityId = 1
            };

            unitOfWork = new Mock<IUnitOfWork>();
            areaRepository = new Mock<IRepository<AreaEntity>>();
            topicRepository = new Mock<IRepository<TopicEntity>>();
            typeRepository = new Mock<IRepository<TypeReqEntity>>();
            unitOfWork.Setup(u => u.AreaRepository).Returns(areaRepository.Object);
            unitOfWork.Setup(u => u.TopicRepository).Returns(topicRepository.Object);
            unitOfWork.Setup(u => u.TypeReqRepository).Returns(typeRepository.Object);

            var configuration = new Mock<IConfiguration>();
            configuration.Setup(c => c["DataImport:Path"]).Returns(".\\Assemblies\\DataImport");
            areaLogic = new AreaLogic(unitOfWork.Object);
            topicLogic = new TopicLogic(unitOfWork.Object);
            typeLogic = new TypeReqLogic(unitOfWork.Object);
            importLogic = new ImportLogic(unitOfWork.Object, configuration.Object, areaLogic, topicLogic, typeLogic);
        }

        [TestMethod]
        public void XmlImport_ExpectOk()
        {
            importer = "Xml";
            Parameter firstParameter = new Parameter();
            firstParameter.Name = "Path";
            firstParameter.Value = Directory.GetCurrentDirectory() + "\\xmlFile.xml";
            parameters = new List<Parameter>() { firstParameter };

            importLogic.ImportEverything(importer, parameters);
            var resultArea = areaLogic.GetByName(area.Name);
            var resultTopic = topicLogic.GetByName(topic.Name);
            var resultType = typeLogic.GetByName(type.Name);

            areaRepository.VerifyAll();
            topicRepository.VerifyAll();
            typeRepository.VerifyAll();

            Assert.IsNotNull(resultArea);
            Assert.IsNotNull(resultTopic);
            Assert.IsNotNull(resultType);
            Assert.AreEqual(area.Name, resultArea.Name);
            Assert.AreEqual(area.Id, resultArea.Id);
            Assert.AreEqual(topic.Name, resultTopic.Name);
            Assert.AreEqual(topic.Id, resultTopic.Id);
            Assert.AreEqual(topic.AreaEntityId, resultTopic.AreaEntityId);
            Assert.AreEqual(type.Id, resultType.Id);
            Assert.AreEqual(type.Name, resultType.Name);
            Assert.AreEqual(type.TopicEntityId, resultType.TopicEntityId);
        }

        [TestMethod]
        public void JsonImport_ExpectOk()
        {
            importer = "Json";
            Parameter firstParameter = new Parameter();
            firstParameter.Name = "Path";
            firstParameter.Value = Directory.GetCurrentDirectory() +"\\jsonFile.json";
            parameters = new List<Parameter>() { firstParameter };

            importLogic.ImportEverything(importer, parameters);
            var resultArea = areaLogic.GetByName(area.Name);
            var resultTopic = topicLogic.GetByName(topic.Name);
            var resultType = typeLogic.GetByName(type.Name);

            areaRepository.VerifyAll();
            topicRepository.VerifyAll();
            typeRepository.VerifyAll();

            Assert.IsNotNull(resultArea);
            Assert.IsNotNull(resultTopic);
            Assert.IsNotNull(resultType);
            Assert.AreEqual(area.Name, resultArea.Name);
            Assert.AreEqual(area.Id, resultArea.Id);
            Assert.AreEqual(topic.Name, resultTopic.Name);
            Assert.AreEqual(topic.Id, resultTopic.Id);
            Assert.AreEqual(topic.AreaEntityId, resultTopic.AreaEntityId);
            Assert.AreEqual(type.Id, resultType.Id);
            Assert.AreEqual(type.Name, resultType.Name);
            Assert.AreEqual(type.TopicEntityId, resultType.TopicEntityId);
        }

    }
}
