using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Controllers;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Text;

namespace IMMRequest.WebApi.Test
{
    [TestClass]
    public class TopicControllerTest
    {
        private IWebApiMapper webApiMapper;
        private Mock<ITopicLogic> topicLogic;
        private TopicController topicController;
        private TopicEntity topic;
        private TopicModelIn topicModelIn;
        private TopicModelOut topicModelOut;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            topic = new TopicEntity
            {
                Id = 1,
                Name = "Contenedores de basura",
                AreaEntityId = 1,
                RequestTypes = new List<TypeReqEntity>()
            };
            topicModelIn = new TopicModelIn
            {
                Id = 1,
                Name = "Contenedores de basura",
                AreaEntityId = 1
            };
            topicModelOut = new TopicModelOut
            {
                Id = 1,
                Name = "Contenedores de basura",
                AreaEntityId = 1
            };
            topicLogic = new Mock<ITopicLogic>();
            topicController = new TopicController(topicLogic.Object, webApiMapper);

        }

        [TestMethod]
        public void AddTopic_ExpectOk()
        {
            topicLogic.Setup(a => a.Add(topic)).Returns(topic.Id);
            topicLogic.Setup(a => a.GetByName(topic.Name)).Returns(topic);

            var result = topicController.Post(topicModelIn);
            var createdResult = result as CreatedResult;
            var modelOut = createdResult.Value as TopicModelOut;

            topicLogic.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(201, createdResult.StatusCode);
            Assert.AreEqual(topicModelIn.Name, modelOut.Name);
        }

        [TestMethod]
        public void AddTopic_ExpectError()
        {
            topicLogic.Setup(a => a.Add(topic)).Throws(new ArgumentException("This topic already exists"));

            var result = topicController.Post(topicModelIn);

            var createdResult = result as BadRequestObjectResult;

            topicLogic.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllTopics_ExpectOk()
        {
            ICollection<TopicEntity> topics = new List<TopicEntity>();
            topics.Add(topic);
            IEnumerable<TopicEntity> topicsEnum = topics;
            topicLogic.Setup(a => a.GetAll()).Returns(topicsEnum);

            ICollection<TopicModelOut> expected = new List<TopicModelOut>() { topicModelOut };

            var result = topicController.Get();
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<TopicModelOut>;

            topicLogic.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllTopics_ExpectError()
        {
            topicLogic.Setup(a => a.GetAll()).Throws(new ArgumentException("There are no topics"));

            var result = topicController.Get();
            var deletedResult = result as BadRequestObjectResult;

            topicLogic.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetTopicByName_ExpectOk()
        {
            topicLogic.Setup(a => a.GetByName(topic.Name)).Returns(topic);

            var expected = topicModelOut;

            var result = topicController.Get(topic.Name);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as TopicModelOut;

            topicLogic.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Id, resultModelOut.Id);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetTopicByName_ExpectError()
        {
            topicLogic.Setup(a => a.GetByName(topic.Name)).Throws(new ArgumentException("Topic not found"));

            var expected = topicModelOut;

            var result = topicController.Get(topic.Name);
            var createdResult = result as BadRequestObjectResult;

            topicLogic.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }
    }
}
