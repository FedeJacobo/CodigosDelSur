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
    public class AreaControllerTest
    {
        private IWebApiMapper webApiMapper;
        private Mock<IAreaLogic> areaLogic;
        private AreaController areaController;
        private AreaEntity area;
        private AreaModelIn areaModelIn;
        private AreaModelOut areaModelOut;

        [TestInitialize]
        public void TestInitialize()
        {
            webApiMapper = new WebApiMapper();
            area = new AreaEntity
            {
                Id = 1,
                Name = "Limpieza",
                Topics = new List<TopicEntity>()
            };
            areaModelIn = new AreaModelIn
            {
                Id = 1,
                Name = "Limpieza"
            };
            areaModelOut = new AreaModelOut
            {
                Id = 1,
                Name = "Limpieza",
            };
            areaLogic = new Mock<IAreaLogic>();
            areaController = new AreaController(areaLogic.Object, webApiMapper);

        }

        [TestMethod]
        public void AddArea_ExpectOk()
        {
            areaLogic.Setup(a => a.Add(area)).Returns(area.Id);
            areaLogic.Setup(a => a.GetByName(area.Name)).Returns(area);

            var result = areaController.Post(areaModelIn);
            var createdResult = result as CreatedResult;
            var modelOut = createdResult.Value as AreaModelOut;

            areaLogic.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(201, createdResult.StatusCode);
            Assert.AreEqual(areaModelIn.Name, modelOut.Name);
        }

        [TestMethod]
        public void AddArea_ExpectError()
        {
            areaLogic.Setup(areaLogic => areaLogic.Add(area)).Throws(new ArgumentException("This area already exists"));

            var result = areaController.Post(areaModelIn);

            var createdResult = result as BadRequestObjectResult;

            areaLogic.VerifyAll();

            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllAreas_ExpectOk()
        {
            ICollection<AreaEntity> areas = new List<AreaEntity>();
            areas.Add(area);
            IEnumerable<AreaEntity> areasEnum = areas;
            areaLogic.Setup(a => a.GetAll()).Returns(areasEnum);

            ICollection<AreaModelOut> expected = new List<AreaModelOut>() { areaModelOut };

            var result = areaController.Get();
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as List<AreaModelOut>;

            areaLogic.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Count, resultModelOut.Count);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAllAreas_ExpectError()
        {
            areaLogic.Setup(a => a.GetAll()).Throws(new ArgumentException("There are no areas"));

            var result = areaController.Get();
            var deletedResult = result as BadRequestObjectResult;

            areaLogic.VerifyAll();
            Assert.IsNotNull(deletedResult);
            Assert.AreEqual(400, deletedResult.StatusCode);
        }

        [TestMethod]
        public void GetAreaByName_ExpectOk()
        {
            areaLogic.Setup(a => a.GetByName(area.Name)).Returns(area);

            var expected = areaModelOut;

            var result = areaController.Get(area.Name);
            var createdResult = result as OkObjectResult;
            var resultModelOut = createdResult.Value as AreaModelOut;

            areaLogic.VerifyAll();
            Assert.IsNotNull(result);
            Assert.IsNotNull(createdResult);
            Assert.IsNotNull(resultModelOut);
            Assert.AreEqual(expected.Id, resultModelOut.Id);
            Assert.AreEqual(200, createdResult.StatusCode);
        }

        [TestMethod]
        public void GetAreaByName_ExpectError()
        {
            areaLogic.Setup(a => a.GetByName(area.Name)).Throws(new ArgumentException("Area not found"));

            var expected = areaModelOut;

            var result = areaController.Get(area.Name);
            var createdResult = result as BadRequestObjectResult;

            areaLogic.VerifyAll();
            Assert.IsNotNull(createdResult);
            Assert.AreEqual(400, createdResult.StatusCode);
        }
    }
}
