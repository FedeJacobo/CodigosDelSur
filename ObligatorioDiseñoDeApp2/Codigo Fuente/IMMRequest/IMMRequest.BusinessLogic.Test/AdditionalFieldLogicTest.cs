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
    public class AdditionalFieldLogicTest
    {
        protected Mock<IRepository<AdditionalFieldEntity>> AFRepository;
        protected Mock<IRepository<TypeReqEntity>> typeRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        private IAdditionalFieldLogic aFLogic;
        private AdditionalFieldEntity testAFEntity;
        private TypeReqEntity testTypeReqEntity;

        [TestInitialize]
        public void TestInitialize()
        {

            testTypeReqEntity = new TypeReqEntity
            {
                Id = 1234,
                Name = "Taxi - Acoso",
                AdditionalFields = new AdditionalFieldEntity[] { new AdditionalFieldEntity() }
            };

            testAFEntity = new AdditionalFieldEntity
            {
                Id = 1234,
                Name = "Matrícula",
                Type = "TEXTO",
                Range = "Radio Taxi-Taxi aeropuerto-Fono Taxi",
                TypeReqEntityId = 1
            };

            AFRepository = new Mock<IRepository<AdditionalFieldEntity>>(MockBehavior.Strict);
            typeRepository = new Mock<IRepository<TypeReqEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(u => u.AdditionalFieldRepository).Returns(AFRepository.Object);
            unitOfWork.Setup(u => u.TypeReqRepository).Returns(typeRepository.Object);
            aFLogic = new AdditionalFieldLogic(unitOfWork.Object);
        }

        [TestMethod]
        public void AddNewAdditionalFieldTextTypeTest()
        {

            AFRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(false).Returns(true).Returns(true);
            typeRepository.Setup(t => t.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            AFRepository.Setup(u => u.Add(It.IsAny<AdditionalFieldEntity>())).Verifiable();
            typeRepository.Setup(t => t.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);
            unitOfWork.Setup(r => r.Save());
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);

            aFLogic.Add(testAFEntity);
            var result = aFLogic.GetById(testAFEntity.Id);

            AFRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAFEntity.Id, result.Id);
            Assert.AreEqual(testAFEntity.Name, result.Name);
        }

        [TestMethod]
        public void AddNewAdditionalFieldDateTypeTest()
        {

            AFRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(false).Returns(true).Returns(true);
            typeRepository.Setup(t => t.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            AFRepository.Setup(u => u.Add(It.IsAny<AdditionalFieldEntity>())).Verifiable();
            typeRepository.Setup(t => t.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);
            unitOfWork.Setup(r => r.Save());
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);

            testAFEntity.Type = AdditionalFieldType.FECHA.ToString();
            testAFEntity.Range ="12/03/21 - 12/03/22";

            aFLogic.Add(testAFEntity);
            var result = aFLogic.GetById(testAFEntity.Id);

            AFRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAFEntity.Id, result.Id);
            Assert.AreEqual(testAFEntity.Name, result.Name);
        }

        [TestMethod]
        public void AddNewAdditionalFieldNumberTypeTest()
        {

            AFRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(false).Returns(true).Returns(true);
            typeRepository.Setup(t => t.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            AFRepository.Setup(u => u.Add(It.IsAny<AdditionalFieldEntity>())).Verifiable();
            typeRepository.Setup(t => t.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);
            unitOfWork.Setup(r => r.Save());
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);

            testAFEntity.Type = AdditionalFieldType.ENTERO.ToString();
            testAFEntity.Range = "2 - 20";

            aFLogic.Add(testAFEntity);
            var result = aFLogic.GetById(testAFEntity.Id);

            AFRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAFEntity.Id, result.Id);
            Assert.AreEqual(testAFEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewAdditionalFieldTypeDoesNotExistErrorTest()
        {
            typeRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(false);
            AFRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(false);

            aFLogic.Add(testAFEntity);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewAdditionalFieldNameAlreadyExistInTypeErrorTest()
        {
            typeRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            AFRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(true);

            aFLogic.Add(testAFEntity);
        }

        [TestMethod]
        public void GetAllAdditionalFieldsTest()
        {
            var afs = new List<AdditionalFieldEntity>() { testAFEntity };
            AFRepository.Setup(x => x.GetAll()).Returns(afs);

            var result = aFLogic.GetAll();

            AFRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(result.FirstOrDefault(), testAFEntity);
        }

        [TestMethod]
        public void GetByIdTestOk()
        {
            AFRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(true);
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);

            var result = aFLogic.GetById(testAFEntity.Id);

            AFRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAFEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByIdNotFoundTest()
        {
            AFRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(false);
            aFLogic.GetById(testAFEntity.Id);

            AFRepository.VerifyAll();
        }

        [TestMethod]
        public void GetByNameTestOk()
        {
            AFRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(true);
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(testAFEntity);

            var result = aFLogic.GetByName(testAFEntity.Name);

            AFRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAFEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByNameNotFoundTest()
        {
            AFRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(false);
            AFRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>()));

            aFLogic.GetByName(testAFEntity.Name);

            AFRepository.VerifyAll();
        }
    }
}

