using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;

namespace IMMRequest.XmlDataImporter.Test
{
    [TestClass]
    public class XmlImporterTest
    {
        private IGenericImporter xmlImporter;
        private AreaEntity firstArea;
        private AreaEntity secondArea;
        private TopicEntity firstTopic;
        private TopicEntity secondTopic;
        private TypeReqEntity firstTypeReq;
        private TypeReqEntity secondTypeReq;

        [TestInitialize]
        public void TestInitialize()
        {
            xmlImporter = new XmlImporter();
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

            ICollection<string> result = xmlImporter.GetTypeParameters();

            Assert.AreEqual(expectedResult.Count, result.Count);
        }

        [TestMethod]
        public void GetName_Expects_Xml()
        {
            string expectedResult = "Xml";
            string result = xmlImporter.GetName();

            Assert.AreEqual(expectedResult, result);
        }

        [TestMethod]
        public void GetAreas_Expects_Ok()
        {
            ICollection<AreaEntity> expectedResult = new List<AreaEntity>();
            expectedResult.Add(firstArea);
            expectedResult.Add(secondArea);

            Parameter param = new Parameter { Name = "Path", Value = "xmlFile.xml" };
            ICollection<Parameter> paramList = new List<Parameter>();
            paramList.Add(param);

            ICollection<AreaEntity> result = xmlImporter.GetAreas(paramList);
            var areaOne = result.FirstOrDefault(a => a.Name == "Area_One");
            var areaTwo = result.FirstOrDefault(a => a.Name == "Area_Two");

            Assert.AreEqual(result.Count, 2);
            Assert.IsTrue(result.Contains(areaOne));
            Assert.IsTrue(result.Contains(areaTwo));
        }

        [TestMethod]
        public void GetTopics_Expects_Ok()
        {
            ICollection<TopicEntity> expectedResult = new List<TopicEntity>();
            expectedResult.Add(firstTopic);
            expectedResult.Add(secondTopic);

            Parameter param = new Parameter { Name = "Path", Value = "xmlFile.xml" };
            ICollection<Parameter> paramList = new List<Parameter>();
            paramList.Add(param);

            ICollection<TopicEntity> result = xmlImporter.GetTopics(paramList);
            var topicOne = result.FirstOrDefault(t => t.Name == "Topic_One");
            var topicTwo = result.FirstOrDefault(t => t.Name == "Topic_Two");

            Assert.AreEqual(result.Count, 2);
            Assert.IsTrue(result.Contains(topicOne));
            Assert.IsTrue(result.Contains(topicTwo));
        }

        [TestMethod]
        public void GetTypeReqs_Expects_Ok()
        {
            ICollection<TypeReqEntity> expectedResult = new List<TypeReqEntity>();
            expectedResult.Add(firstTypeReq);
            expectedResult.Add(secondTypeReq);

            Parameter param = new Parameter { Name = "Path", Value = "xmlFile.xml" };
            ICollection<Parameter> paramList = new List<Parameter>();
            paramList.Add(param);

            ICollection<TypeReqEntity> result = xmlImporter.GetTypeReqs(paramList);
            var typeOne = result.FirstOrDefault(t => t.Name == "TypeReq_One");
            var typeTwo = result.FirstOrDefault(t => t.Name == "TypeReq_Two");

            Assert.AreEqual(result.Count, 2);
            Assert.IsTrue(result.Contains(typeOne));
            Assert.IsTrue(result.Contains(typeTwo));
        }
    }
}
