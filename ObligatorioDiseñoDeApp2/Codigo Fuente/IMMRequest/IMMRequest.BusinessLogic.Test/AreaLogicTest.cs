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
    public class AreaLogicTest
    {
        protected Mock<IRepository<AreaEntity>> areaRepository;
        protected Mock<IUnitOfWork> unitOfWork;
        private AreaLogic areaLogic;
        private AreaEntity testAreaEntity;

        [TestInitialize]
        public void TestInitialize()
        {
            testAreaEntity = new AreaEntity
            {
                Id = 1,
                Name = "Limpieza",
                Topics = new List<TopicEntity>()
            };

            areaRepository = new Mock<IRepository<AreaEntity>>(MockBehavior.Strict);
            unitOfWork = new Mock<IUnitOfWork>();
            unitOfWork.Setup(r => r.AreaRepository).Returns(areaRepository.Object);
            areaLogic = new AreaLogic(unitOfWork.Object);
        }
        [TestMethod]
        public void GetByNameTestOk()
        {
            areaRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(true);
            areaRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(testAreaEntity);

            var result = areaLogic.GetByName(testAreaEntity.Name);

            areaRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAreaEntity.Name, result.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetByNameNotFoundTest()
        {
            areaRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(false);
            areaRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AreaEntity, bool>>>()));
            areaLogic.GetByName(testAreaEntity.Name);

            areaRepository.VerifyAll();
        }

        [TestMethod]
        public void GetAllAreasTest()
        {
            var areas = new List<AreaEntity>() { testAreaEntity };
            areaRepository.Setup(x => x.GetAll()).Returns(areas);

            var result = (IList<AreaEntity>)areaLogic.GetAll();

            areaRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(1, result.Count);
            Assert.AreEqual(result.First(), testAreaEntity);
        }

        [TestMethod]
        public void AddNewAreaTest()
        {
            areaRepository.SetupSequence(x => x.Exists(It.IsAny<Expression<Func<AreaEntity, bool>>>()))
                .Returns(false).Returns(true);
            areaRepository.Setup(u => u.Add(It.IsAny<AreaEntity>())).Verifiable();
            areaRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(testAreaEntity);
            unitOfWork.Setup(r => r.Save());
            areaRepository.Setup(r => r.FirstOrDefault(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(testAreaEntity);

            var result = areaLogic.Add(testAreaEntity);
            var resultFromRepository = unitOfWork.Object.AreaRepository.FirstOrDefault(a => a.Name.Equals("Limpieza"));

            areaRepository.VerifyAll();
            Assert.IsNotNull(result);
            Assert.AreEqual(testAreaEntity.Id, result);
            Assert.AreEqual(testAreaEntity.Name, resultFromRepository.Name);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void AddNewAreaInvalidTest()
        {
            areaRepository.Setup(u => u.Exists(It.IsAny<Expression<Func<AreaEntity, bool>>>())).Returns(true);

            areaLogic.Add(testAreaEntity);

            areaRepository.VerifyAll();
        }
    }
}
