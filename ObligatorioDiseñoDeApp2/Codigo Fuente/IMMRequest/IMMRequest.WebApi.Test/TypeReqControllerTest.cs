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

namespace IMMRequest.WebApi.Test
{
    [TestClass]
    public class TypeReqControllerTest
    {
        private IWebApiMapper webApiMapper;
        private TypeReqEntity typeReq;
        private TypeReqModelOut typeReqModelOut;
        private TypeReqModelIn typeReqModelIn;
        private Mock<ITypeReqLogic> typeReqLogicMock;
        private TypeReqController typeReqController;
        private AdditionalFieldEntity additionalField;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            typeReq = new TypeReqEntity
            {
                Id = 1234,
                Name = "Taxi - Acoso",
                TopicEntityId = 1,
                AdditionalFields = new List<AdditionalFieldEntity> { new AdditionalFieldEntity() }
            };
            typeReqModelOut = new TypeReqModelOut
            {
                Id = 1234,
                Name = "Taxi - Acoso",
            };
            typeReqModelIn = new TypeReqModelIn
            {
                Id = 1234,
                Name = "Taxi - Acoso",
            };
            additionalField = new AdditionalFieldEntity
            {
                Id = 1234,
                Name = "Matrícula",
                Type = AdditionalFieldType.TEXTO.ToString(),
                Range = "Radio Taxi - Taxi aeropuerto - Fono Taxi",
                TypeReqEntityId = 1
            };

            typeReqLogicMock = new Mock<ITypeReqLogic>();
            typeReqController = new TypeReqController(typeReqLogicMock.Object, webApiMapper);
        }

        [TestMethod]
        public void CreateTypeReq_ExpectOk()
        {
            typeReqLogicMock.Setup(a => a.Add(typeReq)).Returns(typeReq.Id);
            typeReqLogicMock.Setup(a => a.GetByName(typeReq.Name)).Returns(typeReq);

            var result = typeReqController.Post(typeReqModelIn);
            var createdResult = result as CreatedResult;
            var modelOut = createdResult.Value as TypeReqModelOut;

            typeReqLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(201, createdResult.StatusCode);
            Assert.AreEqual(typeReqModelIn.Id, modelOut.Id);
        }

        [TestMethod]
        public void CreateTypeReq_ExpectAlreadyExistentTypeReqError()
        {
            typeReqLogicMock.Setup(a => a.Add(typeReq)).Throws(new ArgumentException("This type already exists"));

            var result = typeReqController.Post(typeReqModelIn);

            var createdResult = result as BadRequestObjectResult;

            typeReqLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]

        public void GetAllTypeReqs_ExpectOk()
        {
            ICollection<TypeReqEntity> typeReqs = new List<TypeReqEntity>();
            typeReqs.Add(typeReq);
            IEnumerable<TypeReqEntity> typeReqEnum = typeReqs;
            typeReqLogicMock.Setup(method => method.GetAll()).Returns(typeReqEnum);

            ICollection<TypeReqModelOut> expected = new List<TypeReqModelOut>() { typeReqModelOut };

            var result = typeReqController.Get();
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<TypeReqModelOut>;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllTypeReqs_ExpectError()
        {
            typeReqLogicMock.Setup(method => method.GetAll())
                .Throws(new ArgumentException("There are no types"));

            var result = typeReqController.Get();
            var deletedResult = result as BadRequestObjectResult;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetById_TypeReqModelIn_ExpectOk()
        {
            typeReqLogicMock.Setup(method => method.GetById(typeReq.Id)).Returns(typeReq);

            var expected = typeReqModelOut;

            var result = typeReqController.Get(typeReq.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as TypeReqModelOut;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Id, resultModelOut.Id);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetById_TypeReqModelIn_ExpectError()
        {
            typeReqLogicMock.Setup(method => method.GetById(typeReq.Id))
                .Throws(new ArgumentException("Type not found"));

            var expected = typeReqModelOut;

            var result = typeReqController.Get(typeReq.Id);
            var createdResult = result as BadRequestObjectResult;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_BadTypeReq()
        {
            var modelIn = new TypeReqModelIn();

            typeReqController.ModelState.AddModelError("", "Error");
            var result = typeReqController.Put(0, modelIn);

            var createdResult = result as BadRequestObjectResult;

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_Ok()
        {
            TypeReqEntity updatedTypeReq = typeReq;
            updatedTypeReq.Name = "new name";
            typeReqModelIn.Name = "new name";

            typeReqLogicMock.Setup(a => a.Update(typeReq));
            typeReqLogicMock.Setup(a => a.GetById(typeReq.Id)).Returns(updatedTypeReq);


            var result = typeReqController.Put(typeReq.Id, typeReqModelIn);
            var updatedResult = result as CreatedResult;
            var modelOut = updatedResult.Value as TypeReqModelOut;

            typeReqLogicMock.VerifyAll();

            Assert.IsNotNull(result);
            Assert.IsNotNull(updatedResult);
            Assert.AreEqual(modelOut.Name, typeReqModelIn.Name);
            Assert.AreEqual(201, updatedResult.StatusCode);
        }

        [TestMethod]
        public void Put_Expects_NonExistingTypeReq()
        {
            typeReqLogicMock.Setup(service => service.GetById(typeReq.Id))
                .Throws(new ArgumentException("Type not found"));

            var result = typeReqController.Put(typeReq.Id, typeReqModelIn);

            var createdResult = result as BadRequestObjectResult;

            typeReqLogicMock.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void Delete_Expects_Ok()
        {
            typeReqLogicMock.Setup(service => service.Delete(typeReq.Id));

            var result = typeReqController.Delete(typeReqModelIn.Id);
            var deletedResult = result as OkResult;
            typeReqLogicMock.VerifyAll();

            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(200, deletedResult.StatusCode);
        }

        [TestMethod]
        public void Delete_Expects_NonExistingTypeReq()
        {
            typeReqLogicMock.Setup(service => service.Delete(typeReq.Id)).Throws(new ArgumentException());

            var result = typeReqController.Delete(typeReqModelIn.Id);
            var deletedResult = result as BadRequestObjectResult;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetAdditionalFieldsFromType_ExpectsOk()
        {
            IEnumerable<AdditionalFieldEntity> addfs = new List<AdditionalFieldEntity>() { additionalField };
            typeReqLogicMock.Setup(method => method.GetAdditionalFields(typeReq.Id)).Returns(addfs);

            ICollection<AdditionalFieldEntity> expected = new List<AdditionalFieldEntity>() { additionalField };

            var result = typeReqController.GetAdditionalFields(typeReq.Id);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<AdditionalFieldModelOut>;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAdditionalFieldsFromType_ExpectError()
        {
            typeReqLogicMock.Setup(method => method.GetAdditionalFields(typeReq.Id))
                .Throws(new ArgumentException("Type not found"));

            var result = typeReqController.GetAdditionalFields(typeReq.Id);
            var deletedResult = result as BadRequestObjectResult;

            typeReqLogicMock.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }
    }
}
