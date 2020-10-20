using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

namespace IMMRequest.BusinessLogic.Test
{
    [TestClass]
    public class TopicLogicTest
    {
        protected Mock<IRepository<AreaEntity>> areaRepository;
        protected Mock<IRepository<TopicEntity>> topicRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        private TopicLogic topicLogic;
        private AreaEntity testAreaEntity;
        private TopicEntity testTopicEntity;

        [TestInitialize]
        public void TestInitialize()
        {
            testAreaEntity = new AreaEntity
            {
                Id = 1,
                Name = "Limpieza",
                Topics = new List<TopicEntity>()
            };

            testTopicEntity = new TopicEntity
            {
                Id = 1,
                Name = "Contenedores de basura",
                AreaEntityId = 1,
                RequestTypes = new List<TypeReqEntity>()
            };

            areaRepository = new Mock<IRepository<AreaEntity>>(MockBehavior.Strict);
            topicRepository = new Mock<IRepository<TopicEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(r => r.AreaRepository).Returns(areaRepository.Object);
            unitOfWork.Setup(r => r.TopicRepository).Returns(topicRepository.Object);
            topicLogic = new TopicLogic(unitOfWork.Object);
        }
        [TestMethod]
        public void GetByNameTestOk()
        {
            topicRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(true);
            topicRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(testTopicEntity);

            var result = topicLogic.GetByName(testTopicEntity.Name);

            areaRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testTopicEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByNameNotFoundTest()
        {
            topicRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(false);
            topicRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TopicEntity, bool>>>()));
            topicLogic.GetByName(testTopicEntity.Name);

            topicRepository.VerifyAll();
        }

        [TestMethod]
        public void GetAllTopicsTest()
        {
            var topics = new List<TopicEntity>() { testTopicEntity };
            topicRepository.Setup(x => x.GetAll()).Returns(topics);

            var result = (IList<TopicEntity>)topicLogic.GetAll();

            topicRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count);
            Assert.AreEqual(result.First(), testTopicEntity);
        }

        [TestMethod]
        public void AddNewTopic()
        {
            topicRepository.SetupSequence(x => x.Exists(It.IsAny<Expression<Func<TopicEntity, bool>>>()))
                .Returns(false).Returns(false).Returns(true).Returns(true);
            areaRepository.Setup(x => x.Exists(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(true);
            topicRepository.Setup(u => u.Add(It.IsAny<TopicEntity>())).Verifiable();
            topicRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(testTopicEntity);
            unitOfWork.Setup(r => r.Save());
            topicRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(testTopicEntity);

            topicLogic.Add(testTopicEntity);
            var result = topicLogic.GetByName(testTopicEntity.Name);

            topicRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testTopicEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewTopicInvalidTest()
        {
            topicRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(true);

            topicLogic.Add(testTopicEntity);

            topicRepository.VerifyAll();
        }
    }
}
