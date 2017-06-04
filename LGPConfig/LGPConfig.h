#ifndef _H_LGP_CONFIG_H
#define _H_LGP_CONFIG_H

#include <string>
#include <utility>
#include <vector>
#include <map>

class LGPConfig
{
public:
	LGPConfig(const char* config_file);
	virtual ~LGPConfig();

private:
	LGPConfig(const LGPConfig& rhs) { }
	LGPConfig& operator=(const LGPConfig& rhs) { return *this; }

private:
	unsigned int m_iNumRegisters;
public:
	unsigned int GetNumRegisters() const { return m_iNumRegisters; }

private:
	unsigned int m_iPopulationSize;
public:
	unsigned int GetPopulationSize() const { return m_iPopulationSize; }

private:
	double m_dEpsilon;
public:
	double Epsilon() const { return m_dEpsilon; }

private:
	unsigned int m_iMaxGenerations;
public:
	unsigned int GetMaxGenerations() const { return m_iMaxGenerations; }

private:
	unsigned int iPopLogInterval() const { return m_iPopLogInterval; }

private:
	bool m_bMaximization;
public:
	bool IsMaximization() const { return m_bMaximization; }

private:
	std::string m_PopLogFilePath;
	std::string m_StatsLogFilePath;
	std::string m_RunLogFilePath;
	unsigned int m_iPopLogInterval;
public:
	std::string GetPopLogFilePath() const { return m_PopLogFilePath; }
	std::string GetStatsLogFilePath() const { return m_StatsLogFilePath; }
	std::string GetRunLogFilePath() const { return m_RunLogFilePath; }
	unsigned int GetPopLogInterval() const { return m_iPopLogInterval; }

private:
	double m_micro_mutate_register_rate;
	double m_micro_mutate_operator_rate;
	double m_micro_mutate_constant_rate;
	double m_micro_mutate_constant_standard_deviation;
public:
	double GetMicroMutateRegisterRate() const { return m_micro_mutate_register_rate; }
	double GetMicroMutateOperatorRate() const { return m_micro_mutate_operator_rate; }
	double GetMicroMutateConstantRate() const { return m_micro_mutate_constant_rate; }
	double GetMicroMutateConstantStandardDeviation() const { return m_micro_mutate_constant_standard_deviation; }

private:
	double m_crossover_rate;
	double m_macro_mutation_rate;
	double m_micro_mutation_rate;
public:
	double GetMacroMutationRate() const { return m_macro_mutation_rate; }
	double GetMicroMutationRate() const { return m_micro_mutation_rate; }
	double GetCrossoverRate() const { return m_crossover_rate; }

protected:
	std::vector<std::pair<double, double> > m_constant_regs;
public:
	unsigned int GetConstantRegCount() const { return static_cast<unsigned int>(m_constant_regs.size()); }
public:
	double GetConstantRegValue(unsigned int i) const { return m_constant_regs[i].first; }
	double GetConstantRegWeight(unsigned int i) const { return m_constant_regs[i].second; }

public:
	std::string ToString() const;

protected:
	std::map<std::string, std::string> m_lgp_scripts;
public:
	std::string GetScript(std::string script_name) const;
};

#endif