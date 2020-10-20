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
    public class RequestLogicTest
    {
        protected Mock<IRepository<RequestEntity>> requestRepository;
        protected Mock<IRepository<TypeReqEntity>> typeReqRepository;
        protected Mock<IRepository<UserEntity>> userRepository;
        protected Mock<IRepository<AdditionalFieldEntity>> addFRepository;
        protected Mock<IRepository<TopicEntity>> topicRepository;
        protected Mock<IRepository<AreaEntity>> areaRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        private IRequestLogic requestLogic;
        private RequestEntity testRequestEntity;
        private TypeReqEntity testTypeReqEntity;
        private UserEntity testUserEntity;

        [TestInitialize]
        public void TestInitialize()
        {

            testTypeReqEntity = new TypeReqEntity
            {
                Id = 1234,
                Name = "Taxi - Acoso",
                AdditionalFields = new AdditionalFieldEntity[] { new AdditionalFieldEntity() }
            };

            testRequestEntity = new RequestEntity
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1,
                TypeName = "Contenedor roto",
                Status = "CREADA"
            };

            testUserEntity = new UserEntity
            {
                CompleteName = "Nahuel Kleiman",
                Mail = "nkleiman@gmail.com",
                Password = "password",
                Requests = new List<RequestEntity>()
            };
            
            requestRepository = new Mock<IRepository<RequestEntity>>(MockBehavior.Strict);
            typeReqRepository = new Mock<IRepository<TypeReqEntity>>(MockBehavior.Strict);
            userRepository = new Mock<IRepository<UserEntity>>(MockBehavior.Strict);
            addFRepository = new Mock<IRepository<AdditionalFieldEntity>>(MockBehavior.Strict);
            topicRepository = new Mock<IRepository<TopicEntity>>(MockBehavior.Strict);
            areaRepository = new Mock<IRepository<AreaEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(u => u.RequestRepository).Returns(requestRepository.Object);
            unitOfWork.Setup(r => r.TypeReqRepository).Returns(typeReqRepository.Object);
            unitOfWork.Setup(r => r.UserRepository).Returns(userRepository.Object);
            unitOfWork.Setup(r => r.AdditionalFieldRepository).Returns(addFRepository.Object);
            unitOfWork.Setup(r => r.TopicRepository).Returns(topicRepository.Object);
            unitOfWork.Setup(r => r.AreaRepository).Returns(areaRepository.Object);
            requestLogic = new RequestLogic(unitOfWork.Object);
        }

        [TestMethod]
        public void GetRequestStatusOk()
        {
            requestRepository.Setup(r => r.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntity);
            unitOfWork.Setup(w => w.Save());

            var result = requestLogic.GetRequestStatus(testRequestEntity.Id);
            var expected = testRequestEntity.Status;

            requestRepository.VerifyAll();
            Assert.IsNotNull(expected);
            Assert.AreEqual(result, expected.ToString());
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetRequestStatusError()
        {
            requestRepository.Setup(r => r.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(false);
            requestLogic.GetRequestStatus(testRequestEntity.Id);
        }

        [TestMethod]
        public void AddNewRequestTest()
        {
            requestRepository.SetupSequence(r => r.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(false);
            typeReqRepository.Setup(t => t.Exists(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(true);
            addFRepository.Setup(a => a.Get(It.IsAny<Expression<Func<AdditionalFieldEntity, bool>>>())).Returns(new List<AdditionalFieldEntity>());

            typeReqRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TypeReqEntity, bool>>>())).Returns(testTypeReqEntity);
            topicRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<TopicEntity, bool>>>())).Returns(new TopicEntity());
            areaRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(new AreaEntity());

            userRepository.Setup(t => t.Exists(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(true);
            userRepository.Setup(t => t.FirstOrDefault(It.IsAny<Expression<Func<UserEntity, bool>>>())).Returns(testUserEntity);
            userRepository.Setup(t => t.Update(It.IsAny<UserEntity>())).Verifiable();
            unitOfWork.Setup(r => r.Save());
            requestRepository.Setup(t => t.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntity);
            requestRepository.Setup(t => t.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntity);

            requestLogic.Add(testRequestEntity);
            var result = unitOfWork.Object.RequestRepository.FirstOrDefault(r => r.Id == testRequestEntity.Id);

            requestRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testRequestEntity.Id, result.Id);
            Assert.AreEqual(testRequestEntity.Mail, result.Mail);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewRequestInvalidTest()
        {
            requestRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);

            requestLogic.Add(testRequestEntity);
        }

        [TestMethod]
        public void GetAllRequestsTest()
        {
            var requests = new List<RequestEntity>() { testRequestEntity };
            requestRepository.Setup(x => x.GetAll()).Returns(requests);

            var result = requestLogic.GetAll();

            requestRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count());
            Assert.AreEqual(result.FirstOrDefault(), testRequestEntity);
        }

        [TestMethod]
        public void GetByIdTestOk()
        {
            requestRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntity);

            var result = requestLogic.GetById(testRequestEntity.Id);

            requestRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testRequestEntity.Id, result.Id);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByIdNotFoundTest()
        {
            requestRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(false);
            requestLogic.GetById(testRequestEntity.Id);
        }

        [TestMethod]
        public void GetallByMailTest()
        {
            var requests = new List<RequestEntity>() { testRequestEntity };
            requestRepository.Setup(x => x.GetAll()).Returns(requests);

            var result = requestLogic.GetAllByMail(testRequestEntity.Mail);

            requestRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testRequestEntity.Mail, result.FirstOrDefault().Mail);
        }

        [TestMethod]
        public void UpdateRequestTest()
        {
            var testRequestEntityUpd = new RequestEntity()
            {
                Detail = "Un contenedor",
                ApplicantName = "Fed",
                Mail = "f@gmail.com",
                Phone = "1111111111",
                RequestTypeEntityId = 1,
                Status = "CREADA"
            };

            requestRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntityUpd);
            requestRepository.Setup(u => u.Update(It.IsAny<RequestEntity>())).Verifiable();
            requestRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntityUpd);
            unitOfWork.Setup(r => r.Save());

            requestLogic.Update(testRequestEntityUpd);

            var result = requestLogic.GetById(testRequestEntity.Id);

            requestRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testRequestEntityUpd.Mail, result.Mail);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void UpdateRequestInvalidTest()
        {
            requestRepository.SetupSequence(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(false);

            requestLogic.Update(testRequestEntity);

        }

        [TestMethod]
        public void UpdateRequestStateOkTest()
        {

            var testRequestEntityUpd = new RequestEntity()
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1,
                Status = "ENREVISION"
            };

            requestRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntityUpd);
            requestRepository.Setup(u => u.Update(It.IsAny<RequestEntity>())).Verifiable();
            requestRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntityUpd);
            unitOfWork.Setup(r => r.Save());

            requestLogic.Update(testRequestEntityUpd);

            var result = requestLogic.GetById(testRequestEntity.Id);

            requestRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testRequestEntityUpd.Mail, result.Mail);

        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void UpdateRequestStateInvalidTest1()
        {
            var testRequestEntityUpd = new RequestEntity()
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1,
                Status = "ACEPTADA"
            };

            requestRepository.SetupSequence(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntityUpd);
            requestRepository.Setup(u => u.Update(It.IsAny<RequestEntity>())).Verifiable();

            requestLogic.Update(testRequestEntity);

        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void UpdateRequestStateInvalidTest2()
        {

            var testRequestEntityUpd = new RequestEntity()
            {
                Detail = "Un contenedor roto en la esquina de Av. Italia y Bolivia",
                ApplicantName = "Federico Jacobo",
                Mail = "fedejacobo@gmail.com",
                Phone = "098555666",
                RequestTypeEntityId = 1,
                Status = "ENREVISION"
            };

            testRequestEntityUpd.Status = RequestStatus.FINALIZADA.ToString();

            requestRepository.SetupSequence(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.Setup(u => u.FirstOrDefault(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(testRequestEntityUpd);
            requestRepository.Setup(u => u.Update(It.IsAny<RequestEntity>())).Verifiable();

            requestLogic.Update(testRequestEntity);

        }

        [TestMethod]
        public void AReportTestOk()
        {
            string expected = "Creada (1) = [0]";

            var requests = new List<RequestEntity>() { testRequestEntity };

            requestRepository.SetupSequence(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.SetupSequence(u => u.Get(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(requests);
            var result = requestLogic.ReportA("24-05-2020 18:00", "26-05-2020 19:10", "pepe@hotmail.com");

            Assert.AreEqual(result.ElementAt(0), expected);
        }

        [TestMethod]
        public void BReportTestOk()
        {
            string expected = "Contenedor roto (1)";

            var requests = new List<RequestEntity>() { testRequestEntity };
            var types = new List<TypeReqEntity>() { testTypeReqEntity };

            requestRepository.SetupSequence(u => u.Exists(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(true);
            requestRepository.SetupSequence(u => u.Get(It.IsAny<Expression<Func<RequestEntity, bool>>>())).Returns(requests);

            var result = requestLogic.ReportB("24-05-2020 18:00", "26-05-2020 19:10");

            Assert.AreEqual(result.ElementAt(0), expected);
        }
    }
}
