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
using System.Text;

namespace IMMRequest.WebApi.Test
{
    [TestClass]
    public class AdditionalFieldControllerTest
    {
        private IWebApiMapper webApiMapper;
        private AdditionalFieldEntity additionalField;
        private AdditionalFieldModelOut additionalFieldModelOut;
        private AdditionalFieldModelIn additionalFieldModelIn;
        private Mock<IAdditionalFieldLogic> additionalFieldLogicMock;
        private AdditionalFieldController additionalFieldController;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            additionalField = new AdditionalFieldEntity
            {
                Id = 1234,
                Name = "Matrícula",
                Type = AdditionalFieldType.TEXTO.ToString(),
                Range = "Radio Taxi - Taxi aeropuerto - Fono Taxi",
                TypeReqEntityId = 1
            };
            additionalFieldModelOut = new AdditionalFieldModelOut
            {
                Id = 1234,
                Name = "Matrícula",
                Type = AdditionalFieldType.TEXTO.ToString(),
                Range = "Radio Taxi-Taxi aeropuerto-Fono Taxi"
            };
            additionalFieldModelIn = new AdditionalFieldModelIn
            {
                Id = 1234,
                Name = "Matrícula",
                Type = AdditionalFieldType.TEXTO.ToString(),
                Range = "Radio Taxi-Taxi aeropuerto-Fono Taxi"
            };
            additionalFieldLogicMock = new Mock<IAdditionalFieldLogic>();
            additionalFieldController = new AdditionalFieldController(additionalFieldLogicMock.Object, webApiMapper);
        }

        [TestMethod]
        public void CreateAdditionalField_ExpectOk()
        {
            additionalFieldLogicMock.Setup(userLogic => userLogic.Add(additionalField)).Returns(additionalField.Id);
            additionalFieldLogicMock.Setup(userLogic => userLogic.GetById(additionalField.Id)).Returns(additionalField);

            var result = additionalFieldController.Post(additionalFieldModelIn);
            var createdResult = result as CreatedResult;
            var modelOut = createdResult.Value as AdditionalFieldModelOut;

            additionalFieldLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(201, createdResult.StatusCode);
            Assert.AreEqual(additionalFieldModelIn.Id, modelOut.Id);
        }

        [TestMethod]
        public void CreateAdditionalField_ExpectAlreadyExistentAdditionalFieldError()
        {
            additionalFieldLogicMock.Setup(userLogic => userLogic.Add(additionalField))
                .Throws(new ArgumentException("This additionalField already exists"));

            var result = additionalFieldController.Post(additionalFieldModelIn);

            var createdResult = result as BadRequestObjectResult;

            additionalFieldLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]

        public void GetAllAdditionalField_ExpectOk()
        {
            ICollection<AdditionalFieldEntity> additionalFields = new List<AdditionalFieldEntity>();
            additionalFields.Add(additionalField);
            IEnumerable<AdditionalFieldEntity> additionalFieldEnum = additionalFields;
            additionalFieldLogicMock.Setup(method => method.GetAll()).Returns(additionalFieldEnum);

            ICollection<AdditionalFieldModelOut> expected = new List<AdditionalFieldModelOut>() { additionalFieldModelOut };

            var result = additionalFieldController.Get();
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<AdditionalFieldModelOut>;

            additionalFieldLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllAdditionalFields_ExpectError()
        {
            additionalFieldLogicMock.Setup(method => method.GetAll())
                .Throws(new ArgumentException("There are no additionalFields"));

            var result = additionalFieldController.Get();
            var deletedResult = result as BadRequestObjectResult;

            additionalFieldLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetById_AdditionalFieldModelIn_ExpectOk()
        {
            additionalFieldLogicMock.Setup(method => method.GetById(additionalField.Id)).Returns(additionalField);

            var expected = additionalFieldModelOut;

            var result = additionalFieldController.Get(additionalField.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as AdditionalFieldModelOut;

            additionalFieldLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Id, resultModelOut.Id);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetById_AdditionalFieldModelIn_ExpectError()
        {
            additionalFieldLogicMock.Setup(method => method.GetById(additionalField.Id))
                .Throws(new ArgumentException("AdditionalField not found"));

            var expected = additionalFieldModelOut;

            var result = additionalFieldController.Get(additionalField.Id);
            var createdResult = result as BadRequestObjectResult;

            additionalFieldLogicMock.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }
    }
}
