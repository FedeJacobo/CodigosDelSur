using IMMRequest.BusinessLogic.Interfaces;
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
    public class TypeReqLogicTest
    {
        protected Mock<IRepository<TypeReqEntity>> typeReqRepository;
        protected Mock<IRepository<TopicEntity>> topicRepository;
        protected Mock<IRepository<AdditionalFieldEntity>> aFRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        private ITypeReqLogic typeReqLogic;
        private TypeReqEntity testTypeReqEntity;
        private AdditionalFieldEntity testAFEntity;

        [TestInitialize]
        public void TestInitialize()
        {
            testTypeReqEntity = new TypeReqEntity
            {
                Id = 1234,
                Name = "Taxi - Acoso",
                AdditionalFields = new List<AdditionalFieldEntity>()
            };

            testAFEntity = new AdditionalFieldEntity
            {
                Id = 1234,
                Name = "Matrícula",
                Type = "TEXTO",
                Range = "Radio Taxi-Taxi aeropuerto-Fono Taxi",
                TypeReqEntityId = 1
            };

            typeReqRepository = new Mock<IRepository<TypeReqEntity>>(MockBehavior.Strict);
            topicRepository = new Mock<IRepository<TopicEntity>>(MockBehavior.Strict);
            aFRepository = new Mock<IRepository<AdditionalFieldEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(r => r.TypeReqRepository).Returns(typeReqRepository.Object);
            unitOfWork.Setup(r => r.TopicRepository).Returns(topicRepository.Object);
            unitOfWork.Setup(r => r.AdditionalFieldRepository).Returns(aFRepository.Object);
            typeReqLogic = new TypeReqLogic(unitOfWork.Object);
        }

        [TestMethod]
        public void AddNewTypeReqTest()
        {
            typeReqRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>()))
                .Returns(false).Returns(false).Returns(true);
            topicRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(true); ;
            typeReqRepository.Setup(u => u.Add(It.IsAny<TypeReqEntity>())).Verifiable();
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>()))
                .Returns(testTypeReqEntity);
            unitOfWork.Setup(r => r.Save());
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>()))
                .Returns(testTypeReqEntity);

            typeReqLogic.Add(testTypeReqEntity);
            var result = unitOfWork.Object.TypeReqRepository.FirstOrDefault(t => t.Id == testTypeReqEntity.Id);

            typeReqRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testTypeReqEntity.Id, result.Id);
            Assert.AreEqual(testTypeReqEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewTypeReqInvalidTest()
        {
            typeReqRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);

            typeReqLogic.Add(testTypeReqEntity);

            typeReqRepository.VerifyAll();
        }

        [TestMethod]
        public void GetAllTypeReqsTest()
        {
            var types = new List<TypeReqEntity>() { testTypeReqEntity };
            typeReqRepository.Setup(x => x.GetAll()).Returns(types);

            var result = typeReqLogic.GetAll();

            typeReqRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(result.FirstOrDefault(), testTypeReqEntity);
        }

        [TestMethod]
        public void GetByIdTestOk()
        {
            typeReqRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);

            var result = typeReqLogic.GetById(testTypeReqEntity.Id);

            typeReqRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testTypeReqEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByIdNotFoundTest()
        {
            typeReqRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(false);
            typeReqLogic.GetById(testTypeReqEntity.Id);

            typeReqRepository.VerifyAll();
        }

        [TestMethod]
        public void GetByNameTestOk()
        {
            typeReqRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);

            var result = typeReqLogic.GetByName(testTypeReqEntity.Name);

            typeReqRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testTypeReqEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByNameNotFoundTest()
        {
            typeReqRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(false);
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>()));
            typeReqLogic.GetByName(testTypeReqEntity.Name);

            typeReqRepository.VerifyAll();
        }

        [TestMethod]
        public void DeleteTypeReqTest()
        {
            typeReqRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);
            typeReqRepository.Setup(r => r.Update(It.IsAny<TypeReqEntity>())).Verifiable();
            aFRepository.Setup(a => a.Get(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(new List<AdditionalFieldEntity>());
            unitOfWork.Setup(r => r.Save());

            typeReqLogic.Delete(testTypeReqEntity.Id);

            typeReqRepository.VerifyAll();
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void DeleteTypeReqNotFoundTest()
        {
            typeReqRepository.Setup(r => r.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(false);

            typeReqLogic.Delete(testTypeReqEntity.Id);
            typeReqRepository.VerifyAll();
        }

        [TestMethod]
        public void UpdateTypeReqTest()
        {
            var testTypeReqEntityUpd = new TypeReqEntity
            {
                Id = 1234,
                Name = "Tax",
                AdditionalFields = new AdditionalFieldEntity[] { new AdditionalFieldEntity() }
            };

            typeReqRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            typeReqRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntityUpd);
            typeReqRepository.Setup(u => u.Update(It.IsAny<TypeReqEntity>())).Verifiable();
            typeReqRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntityUpd);
            unitOfWork.Setup(r => r.Save());

            typeReqLogic.Update(testTypeReqEntity);

            var result = typeReqLogic.GetById(testTypeReqEntityUpd.Id);

            typeReqRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testTypeReqEntityUpd.Name, result.Name);
        }

        [TestMethod]
        public void GetAdditionalFieldsFromTypeTest()
        {
            testTypeReqEntity.AdditionalFields.Add(testAFEntity);
            typeReqRepository.Setup(w => w.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            aFRepository.Setup(w => w.GetAll()).Returns(testTypeReqEntity.AdditionalFields);
            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);

            var result = typeReqLogic.GetAdditionalFields(testTypeReqEntity.Id);

            typeReqRepository.VerifyAll();
            Assert.IsNotNull(result);
        }
    }
}
