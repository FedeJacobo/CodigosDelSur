using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.DataAccess.Interfaces;
using IMMRequest.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace IMMRequest.BusinessLogic
{
    public class TopicLogic : ITopicLogic
    {
        private readonly IUnitOfWork unitOfWork;
        public TopicLogic(IUnitOfWork unitOfWork)
        {
            this.unitOfWork = unitOfWork;
        }

        public int Add(TopicEntity topic)
        {
            ValidateTopicIsNotRepeated(topic);
            ValidateAreaForTopicExists(topic);
            ValidateRepeatedTopicNameInArea(topic);

            unitOfWork.TopicRepository.Add(topic);
            unitOfWork.Save();
            return this.GetByName(topic.Name).Id;
        }

        private void ValidateTopicIsNotRepeated(TopicEntity topic)
        {
            if (TopicExists(topic.Id))
                throw new ArgumentException($"Topic with id: {topic.Id} already exist");
        }

        private bool TopicExists(int id)
        {
            return unitOfWork.TopicRepository.Exists(a => a.Id == id);
        }

        private void ValidateAreaForTopicExists(TopicEntity topic)
        {
            if (!AreaForTopicExists(topic))
                throw new ArgumentException($"Area with id: {topic.AreaEntityId} does not exist");
        }

        private bool AreaForTopicExists(TopicEntity topic)
        {
            return unitOfWork.AreaRepository.Exists(t => t.Id == topic.AreaEntityId);
        }

        private void ValidateRepeatedTopicNameInArea(TopicEntity topic)
        {
            if (TopicNameIsRepeatedInArea(topic))
                throw new ArgumentException($"There is already a topic with name {topic.Name} in the area with id: {topic.AreaEntityId}");
        }

        private bool TopicNameIsRepeatedInArea(TopicEntity topic)
        {
            return unitOfWork.TopicRepository.Exists(a => a.Name == topic.Name && a.AreaEntityId == topic.AreaEntityId);
        }

        public TopicEntity GetByName(string name)
        {
            ValidateTopicNameExistance(name);
            TopicEntity result = unitOfWork.TopicRepository.FirstOrDefault(u => u.Name == name);
            return result;
        }

        private void ValidateTopicNameExistance(string name)
        {
            if (!TopicNameExists(name))
                throw new ArgumentException($"Topic with name: {name} doesn't exist");
        }

        private bool TopicNameExists(string name)
        {
            return unitOfWork.TopicRepository.Exists(a => a.Name == name);
        }

        public IEnumerable<TopicEntity> GetAll()
        {
            IEnumerable<TopicEntity> topics = unitOfWork.TopicRepository.GetAll();
            return topics;
        }
    }
}
