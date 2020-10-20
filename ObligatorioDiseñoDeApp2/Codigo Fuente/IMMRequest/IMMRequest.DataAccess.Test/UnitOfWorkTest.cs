using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.DataAccess.Test
{
    [TestClass]
    public class UnitOfWorkTest
    {
        IUnitOfWork unitOfWork;
        Context context;

        [TestInitialize]
        public void TestInitialize()
        {
            var options = new DbContextOptionsBuilder<Context>().UseInMemoryDatabase(databaseName: "TestDatabase").Options;
            context = new Context(options);
            unitOfWork = new UnitOfWork(context);
        }

        [TestMethod]
        public void GetAdditionalFieldRepo()
        {
            IRepository<AdditionalFieldEntity> result = unitOfWork.AdditionalFieldRepository;

            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void GetRequestRepo()
        {
            IRepository<RequestEntity> result = unitOfWork.RequestRepository;

            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void GetSessiontRepo()
        {
            IRepository<SessionEntity> result = unitOfWork.SessionRepository;

            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void GetTopictRepo()
        {
            IRepository<TopicEntity> result = unitOfWork.TopicRepository;

            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void GetTypeReqtRepo()
        {
            IRepository<TypeReqEntity> result = unitOfWork.TypeReqRepository;

            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void GetUserRepo()
        {
            IRepository<UserEntity> result = unitOfWork.UserRepository;

            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void SaveOk()
        {
            unitOfWork.Save();
        }

        [TestMethod]
        public void DisposeOk()
        {
            unitOfWork.Dispose();
        }
    }
}
