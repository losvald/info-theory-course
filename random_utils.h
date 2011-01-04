/*
 * random_utils.h
 * 
 * Copyright (C) 2010 Leo Osvald <leo.osvald@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License.
 *  
 * You may obtain a copy of the License at 
 * 		http://www.apache.org/licenses/LICENSE-2.0
 *  
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and 
 * limitations under the License. 
 */
/*
 * random_utils.h
 *
 *  Created on: Apr 22, 2010
 *      Author: Leo Osvald
 */

#ifndef RANDOM_UTILS_H_
#define RANDOM_UTILS_H_

#include <cstdlib>
#include <ctime>

#include <vector>
#include <set>
#include <iostream>

class RandomUtils {
public:
	class BadRandomRangeException {
	};

protected:
	static unsigned default_seed_val_;
	static unsigned* seed_;
private:


protected:
	template<typename T>
	static T random(unsigned* seed) {
		int bits = 12;
		T r = 0;
		 //-1 is intentional coz of unsigned and signed
		for(int i = sizeof(r)*8-1; i > 0; i -= bits) {
			if(i < bits)
				bits = i;
			r = (r<<bits) | rand_r(seed)%(1<<bits);
		}
		return r;
	}

public:
	static unsigned new_seed_val();
	static unsigned new_seed_val(const unsigned* address_offset);

	template<typename T>
	static T random(const std::pair<T, T>& range, unsigned* seed) {
		if(range.second <= range.first) {
			std::cerr << "Invalid range: " << range.first << " " << range.second
					<< std::endl;
			throw BadRandomRangeException();
		}
		return random<T>(seed)%(range.second-range.first) + range.first;
	}

	template<typename T>
	static T random(const std::pair<T, T>& range) {
		return random<T>(range, seed_);
	}

	template<typename T>
	static std::vector<T> random_vector(int n,
			const std::pair<T, T>& range, unsigned* seed) {

		std::vector<T> v(n);
		for(int i = 0; i < n; ++i)
			v[i] = random(range, seed);
		return v;
	}

	template<typename T>
	static std::vector<T> random_vector(int n,
			const std::pair<T, T>& range) {
		return random_vector<T>(n, range, seed_);
	}

	template<typename T>
	static std::set<T> random_set(int n,
				const std::pair<T, T>& range, unsigned* seed) {
		std::set<T> s;
		int w = range.second-range.first+1;
		if(n > w) n = w;
		while(n > 0) {
			int r = random(range, seed);
			if(s.find(r) == s.end()) {
				s.insert(r);
				--n;
			}
		}
		return s;
	}

	template<typename T>
	static std::pair<T, T> fromInclusiveRange(const std::pair<T, T>& range) {
		return std::make_pair<T, T>(range.first, range.second+1);
	}

public:
	class SeedClass {
	protected:
		mutable unsigned *seed_;
		mutable unsigned seed_val_;
	public:
		SeedClass() {
			set_seed_val(RandomUtils::new_seed_val(&seed_val_));
		}
		SeedClass(unsigned seed_val) {
			set_seed_val(seed_val);
		}
		void set_seed_val(unsigned seed_val) const {
			seed_val_ = seed_val;
		}
		unsigned* seed() {
			return seed_;
		}
	};


	template<class T>
	class DiscreteRandomVariable {
	private:
		std::vector<int> sum_;
		std::vector<T> outcomes_;
		T not_found_val_;
		mutable unsigned* seed_;
		mutable unsigned seed_val_;
		static const short MAX_ABSOLUTE_PROBABILITY = 0x7fff;
	public:
		DiscreteRandomVariable(T not_found_val) : not_found_val_(not_found_val) {
			init();
		}

		DiscreteRandomVariable() : not_found_val_(-1) {
			init();
		}

		/**
		 * Vraca ishod koji je ostvaren.<br>
		 */
		T get() const {
			if(sum_.empty())
				return not_found_val_;
			int totalSum = sum_.at(sum_.size()-1);
			if(totalSum <= 0)
				return not_found_val_;
			int target = random(std::make_pair(0, totalSum), seed_);
			int lo = 0, hi = sum_.size()-1;
			while(lo < hi) {
				int mid = lo + (hi-lo-1)/2;
				if(target < sum_.at(mid))
					hi = mid;
				else
					lo = mid+1;
			}
			return outcomes_.at(lo);
		}


		void add(T outcome, double probability) {
			int s = absoluteProbability(probability)
						+ (!sum_.empty() ? sum_.at(sum_.size()-1) : 0);
			outcomes_.push_back(outcome);
			sum_.push_back(s);
		}

		void remove(T outcome) {
			int ind = indexOf(outcome);
			if(ind != -1) {
				int d = getAbsoluteProbabilityAt(ind);
				sum_.erase(sum_.begin()+ind);
				outcomes_.erase(outcomes_.begin()+ind);
				fix(ind, -d);
			}
		}

		void clear() {
			std::vector<T> v = outcomes_;
			for(; !v.empty(); v.pop_back())
				remove(v.back());
		}

		void setProbability(T outcome, double probability) {
			short absolute_prob = absoluteProbability(probability);
			int ind = indexOf(outcome);
			if(ind != -1) {
				fix(ind, absolute_prob - getAbsoluteProbabilityAt(ind));
			}
		}

		/**
		 * Vraca vjerojatnost da bude izabran zadani ishod (posao).
		 * @param outcome ishod (posao)
		 * @return vjerojatnost
		 */
		double getProbability(T outcome) const {
			int ind = indexOf(outcome);
			if(ind == -1)
				return 0;
			return (double)getAbsoluteProbabilityAt(ind)/sum_.at(sum_.size()-1);
		}

		std::vector< std::pair<T, double> > getDistribution() const {
			std::vector< std::pair<T, double> > d(outcomes_.size());
			for(int i = 0; i < (int)outcomes_.size(); ++i) {
				d[i] = std::make_pair(outcomes_.at(i),
						getProbability(outcomes_.at(i)));
			}
			return d;
		}

		void set_seed(unsigned seed) {
			seed_val_ = seed;
			seed_ = &seed_val_;
		}

		unsigned seed_value() const {
			return seed_val_;
		}

	private:

		short absoluteProbability(double probability) const {
			if(probability < 0) return 0;
			if(probability >= 1) return MAX_ABSOLUTE_PROBABILITY;
			return (short) (probability * MAX_ABSOLUTE_PROBABILITY);
		}

		double relativeProbability(short absoluteProbability) const {
			return (double) absoluteProbability / MAX_ABSOLUTE_PROBABILITY;
		}

		void fix(int from, int sumDiff) {
			for(int i = from; i < (int)sum_.size(); ++i)
				sum_[i] += sumDiff;
		}

		int getAbsoluteProbabilityAt(int index) const {
			return sum_.at(index)
						- (index > 0 ? sum_.at(index-1) : 0);
		}

		int indexOf(T outcome) const {
			for(int i = 0; i < (int)outcomes_.size(); ++i)
				if(outcomes_[i] == outcome)
					return i;
			return -1;
		}

		void init() {
			seed_val_ = (unsigned)time(NULL);
			seed_ = &seed_val_;
		}
	};

};

#endif /* RANDOM_UTILS_H_ */
