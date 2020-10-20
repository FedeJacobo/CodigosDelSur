using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.JsonDataImporter.Test
{
    [TestClass]
    public class JsonImporterTest
    {
        private IGenericImporter jsonImporter;
        private AreaEntity firstArea;
        private AreaEntity secondArea;
        private TopicEntity firstTopic;
        private TopicEntity secondTopic;
        private TypeReqEntity firstTypeReq;
        private TypeReqEntity secondTypeReq;

        [TestInitialize]
        public void TestInitialize()
        {
            jsonImporter = new JsonImporter();
            firstArea = new AreaEntity
            {
                Name = "Area_One",
            };
            secondArea = new AreaEntity
            {
                Name = "Area_Two",
            };
            firstTopic = new TopicEntity
            {
                Name = "Topic_One",
                AreaEntityId = 2,
            };
            secondTopic = new TopicEntity
            {
                Name = "Topic_Two",
                AreaEntityId = 2,
            };
            firstTypeReq = new TypeReqEntity
            {
                Name = "TypeReq_One",
                TopicEntityId = 1,
            };
            secondTypeReq = new TypeReqEntity
            {
                Name = "TypeReq_Two",
                TopicEntityId = 2,
            };
        }

        [TestMethod]
        public void GetParameters_Expects_Ok()
        {
            ICollection<Parameter> expectedResult = new List<Parameter>();
            Parameter expectedParam = new Parameter { Value = "Path" };
            expectedResult.Add(expectedParam);

            ICollection<string> result = jsonImporter.GetTypeParameters();

            Assert.AreEqual(expectedResult.Count, result.Count);
            Assert.AreEqual(result.OfType<string>().FirstOrDefault(), "Path");
        }

        [TestMethod]
        public void GetName_Expects_Json()
        {
            string expectedResult = "Json";
            string result = jsonImporter.GetName();

            Assert.AreEqual(expectedResult, result);
        }

        [TestMethod]
        public void GetAreas_Expects_Ok()
        {
            ICollection<AreaEntity> expectedResult = new List<AreaEntity>();
            expectedResult.Add(firstArea);
            expectedResult.Add(secondArea);

            Parameter param = new Parameter { Name = "Path", Value = "jsonFile.json" };
            ICollection<Parameter> paramList = new List<Parameter>();
            paramList.Add(param);

            ICollection<AreaEntity> result = jsonImporter.GetAreas(paramList);
            var areaOne = result.FirstOrDefault(a => a.Id == 1);
            var areaTwo = result.FirstOrDefault(a => a.Id == 2);

            Assert.AreEqual(result.Count, 2);
        }

        [TestMethod]
        public void GetTopics_Expects_Ok()
        {
            ICollection<TopicEntity> expectedResult = new List<TopicEntity>();
            expectedResult.Add(firstTopic);
            expectedResult.Add(secondTopic);

            Parameter param = new Parameter { Name = "Path", Value = "jsonFile.json" };
            ICollection<Parameter> paramList = new List<Parameter>();
            paramList.Add(param);

            ICollection<TopicEntity> result = jsonImporter.GetTopics(paramList);
            var topicOne = result.FirstOrDefault(t => t.Id == 1);
            var topicTwo = result.FirstOrDefault(t => t.Id == 2);

            Assert.AreEqual(result.Count, 2);
        }

        [TestMethod]
        public void GetTypeReqs_Expects_Ok()
        {
            ICollection<TypeReqEntity> expectedResult = new List<TypeReqEntity>();
            expectedResult.Add(firstTypeReq);
            expectedResult.Add(secondTypeReq);

            Parameter param = new Parameter { Name = "Path", Value = "jsonFile.json" };
            ICollection<Parameter> paramList = new List<Parameter>();
            paramList.Add(param);

            ICollection<TypeReqEntity> result = jsonImporter.GetTypeReqs(paramList);

            Assert.AreEqual(result.Count, 2);;
        }
    }
}
