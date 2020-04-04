# Motivation
If you're a student trying to learn picture <-> name relation this is for you. The target application of it is to be a simple tester program in particular for bio-preparation learning. In general case it's user-extensible. To create your own test just load `.xml` file consisting of a definitions of each `object`. You can link an unbounded count of `photo`s to each `subject`.
Each test file should be signed by author and belong to subject/theme pair.

### TODO
1. [x] upgrade xml reading with QXmlSimpleReader & Handlers  
2. [x] make a simple .xsd & validate input sources with it  
3. [ ] make a list of existent tests (sqlite or flat file)  
4. [ ] make test constructor with drag & drop feature
5. [ ] make it distributable
	- [ ] migrate to cmake build
	- [ ] light unit tests coverage
	- [ ] build & test continiously @travisCI
	- [ ] deploy @github
	