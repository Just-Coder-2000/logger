#pragma once

/**
 * @file logger.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

/**
 * @brief the main message type macroes and methods
 * 
 * [1] info    {Information; Message; real-time info Of information; Of messages; Informative}
 * [2] process {The process of achieving a goal; The development of things, especially the steps of natural change;}
 * [3] warning {about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered}
 * [4] error   {Error; Errors; Fallacy;}
 * [5] fatal   {Fatal; Catastrophic; Destructive; Cause failure}
 * 
 * [6] void setCurOS(std::ostream &os) set the output stream
 * 
 */

namespace ns_log
{
    namespace ns_priv
    {
        /**
         * @brief the ostream
         */
        static std::ostream *logerOS = &(std::cout);

        /**
         * @brief Get the current ostream
         * 
         * @return std::ostream& 
         */
        static std::ostream &getCurOS() { return *(ns_priv::logerOS); }

        struct Logger
        {
        private:
            /**
             * @brief the members
             */
            std::string _desc;
            bool _firCall;

        public:
            /**
             * @brief construct a new Logger object
             */
            Logger(const std::string &desc)
                : _desc(desc), _firCall(true) {}

            inline std::string &desc() { return this->_desc; }
            inline const std::string &desc() const { return this->_desc; }

            /**
             * @brief overload the operator '()'
             */
            void operator()()
            {
                auto [h, m, s] = Logger::curTime();
                ns_priv::getCurOS() << this->_desc << " [" << h << ':' << m << ':' << s << "] " << '\n';
                this->_firCall = true;
                return;
            }

            /**
             * @brief overload the operator '()'
             */
            template <typename ArgvType>
            void operator()(const ArgvType &argv)
            {
                if (this->_firCall)
                {
                    auto [h, m, s] = Logger::curTime();
                    ns_priv::getCurOS() << this->_desc << " [" << h << ':' << m << ':' << s << "] ";
                }
                ns_priv::getCurOS() << argv << '\n';
                this->_firCall = true;
                return;
            }

            /**
             * @brief overload the operator '()'
             */
            template <typename ArgvType, typename... ArgvsType>
            void operator()(const ArgvType &argv, const ArgvsType &...argvs)
            {
                if (this->_firCall)
                {
                    auto [h, m, s] = Logger::curTime();
                    ns_priv::getCurOS() << this->_desc << " [" << h << ':' << m << ':' << s << "] " << argv;
                    this->_firCall = false;
                }
                else
                    ns_priv::getCurOS() << argv;
                return (*this)(argvs...);
            }

        protected:
            /**
             * @brief get the time when the message is outputed
             * 
             * @return std::tuple<uint, uint, uint> 
             */
            static std::tuple<uint, uint, uint> curTime()
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);
                return {ltm->tm_hour, ltm->tm_min, ltm->tm_sec};
            }
        };

        static Logger info("[ info  ]"), process("[process]"), warning("[warning]"), error("[ error ]"), fatal("[ fatal ]");
    } // namespace ns_priv

    /**
     * @brief Set the current ostream
     * 
     * @param os the ostream
     */
    static void setCurOS(std::ostream &os) { ns_priv::logerOS = &os; }

/**
 * @brief the main message type macroes
 * 
 * [1] info    {Information; Message; real-time info Of information; Of messages; Informative}
 * [2] process {The process of achieving a goal; The development of things, especially the steps of natural change;}
 * [3] warning {about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered}
 * [4] error   {Error; Errors; Fallacy;}
 * [5] fatal   {Fatal; Catastrophic; Destructive; Cause failure}
 * 
 */
#define INFO(...) ns_log::ns_priv::info(__VA_ARGS__)
#define PROCESS(...) ns_log::ns_priv::process(__VA_ARGS__)
#define WARNING(...) ns_log::ns_priv::warning(__VA_ARGS__)
#define ERROR(...) ns_log::ns_priv::error(__VA_ARGS__)
#define FATAL(...) ns_log::ns_priv::fatal(__VA_ARGS__)

} // namespace ns_log
