@echo off
mkdir Chapters 2>nul
mkdir Quizzes 2>nul

:: ─── CHAPTERS ──────────────────────────────────────────────────────────────

(
echo Chapter: Object-Oriented Programming ^(OOP^)
echo Author: AI Learning Assistant
echo =====================================================
echo.
echo INTRODUCTION
echo ------------
echo Object-Oriented Programming is a programming paradigm
echo built around real-world "objects". Each object bundles
echo data ^(attributes^) and behavior ^(methods^) together.
echo.
echo THE 4 PILLARS OF OOP
echo ---------------------
echo 1. ENCAPSULATION
echo    Wrapping data and functions inside a class.
echo    Private members can only be accessed via getters/setters.
echo    Example: score is private; use getScore^(^) to read it.
echo.
echo 2. ABSTRACTION
echo    Hiding complex details, showing only essentials.
echo    Abstract classes use pure virtual functions.
echo    Example: virtual void display^(^) = 0;
echo.
echo 3. INHERITANCE
echo    A derived class acquires properties of a base class.
echo    Promotes code reuse and hierarchical relationships.
echo    Example: class Student : public User {}
echo.
echo 4. POLYMORPHISM
echo    One interface, many implementations.
echo    Achieved via function overriding and virtual functions.
echo    Example: display^(^) behaves differently in each subclass.
echo.
echo KEY CONCEPTS
echo ------------
echo - Constructor: Special method called when object is created.
echo - Destructor:  Cleans up when object is destroyed.
echo - Composition: A class contains objects of another class.
echo - Dynamic Binding: Function call resolved at runtime.
) > Chapters\OOP.txt

(
echo Chapter: Introduction to Genetics
echo Author: AI Learning Assistant
echo =====================================================
echo.
echo INTRODUCTION
echo ------------
echo Genetics is the scientific study of genes, heredity,
echo and variation in living organisms. It explains how
echo traits are passed from parents to offspring.
echo.
echo KEY TERMS
echo ---------
echo DNA  - Deoxyribonucleic acid, the hereditary molecule.
echo Gene - A segment of DNA that codes for a protein.
echo Allele - Different forms of the same gene.
echo Genome - The complete set of genes of an organism.
echo.
echo MENDEL'S LAWS
echo -------------
echo 1. Law of Segregation: Each trait is controlled by a
echo    pair of alleles that separate during gamete formation.
echo.
echo 2. Law of Independent Assortment: Genes for different
echo    traits are inherited independently of each other.
echo.
echo DNA STRUCTURE
echo -------------
echo - Double helix shape, discovered by Watson and Crick.
echo - Made of nucleotides: Adenine, Thymine, Guanine, Cytosine.
echo - A pairs with T, G pairs with C.
echo - Stores and transmits genetic information.
) > Chapters\Genetics.txt

(
echo Chapter: Data Structures
echo Author: AI Learning Assistant
echo =====================================================
echo.
echo INTRODUCTION
echo ------------
echo A data structure organizes and stores data efficiently
echo so it can be accessed and modified effectively.
echo.
echo TYPES OF DATA STRUCTURES
echo -------------------------
echo 1. ARRAY
echo    Fixed-size collection of same-type elements.
echo    Access by index. O^(1^) access, O^(n^) search.
echo.
echo 2. LINKED LIST
echo    Nodes connected by pointers. Dynamic size.
echo    O^(n^) access, O^(1^) insert/delete at head.
echo.
echo 3. STACK
echo    LIFO - Last In First Out.
echo    Operations: push^(^), pop^(^), peek^(^).
echo    Example: Undo feature in text editors.
echo.
echo 4. QUEUE
echo    FIFO - First In First Out.
echo    Operations: enqueue^(^), dequeue^(^).
echo    Example: Printer job scheduling.
echo.
echo 5. BINARY TREE
echo    Each node has at most 2 children.
echo    Used in searching and sorting algorithms.
echo.
echo COMPLEXITY
echo ----------
echo Big-O notation measures algorithm efficiency.
echo O^(1^) = Constant   O^(n^) = Linear   O^(log n^) = Logarithmic
) > Chapters\DataStructures.txt

(
echo Chapter: Biochemistry Basics
echo Author: AI Learning Assistant
echo =====================================================
echo.
echo INTRODUCTION
echo ------------
echo Biochemistry is the study of chemical processes
echo occurring within and relating to living organisms.
echo It bridges biology and chemistry.
echo.
echo BIOMOLECULES
echo ------------
echo 1. PROTEINS
echo    Made of amino acids. Perform most cell functions.
echo    Examples: enzymes, antibodies, structural proteins.
echo.
echo 2. CARBOHYDRATES
echo    Primary energy source. Made of C, H, O.
echo    Glucose = C6H12O6. Stored as glycogen in animals.
echo.
echo 3. LIPIDS
echo    Fats, oils, waxes. Energy storage, membrane structure.
echo    Hydrophobic - do not dissolve in water.
echo.
echo 4. NUCLEIC ACIDS
echo    DNA and RNA. Store and transmit genetic information.
echo    Monomers are nucleotides.
echo.
echo ENZYMES
echo -------
echo Biological catalysts that speed up chemical reactions.
echo Each enzyme is specific to one substrate ^(lock and key^).
echo Temperature and pH affect enzyme activity.
) > Chapters\Biochemistry.txt

(
echo Chapter: Molecular Biology
echo Author: AI Learning Assistant
echo =====================================================
echo.
echo INTRODUCTION
echo ------------
echo Molecular Biology studies the molecular basis of
echo biological activity, especially DNA, RNA, and proteins.
echo.
echo CENTRAL DOGMA
echo -------------
echo DNA -^> RNA -^> Protein
echo 1. Transcription: DNA is copied into mRNA in nucleus.
echo 2. Translation: mRNA is read by ribosome to make protein.
echo.
echo DNA REPLICATION
echo ---------------
echo - Occurs before cell division.
echo - Helicase unwinds the double helix.
echo - DNA Polymerase adds complementary bases.
echo - Results in two identical daughter DNA strands.
echo.
echo MUTATIONS
echo ---------
echo A mutation is a change in the DNA sequence.
echo Types: Point mutation, Insertion, Deletion, Inversion.
echo Mutations can be harmless, harmful, or beneficial.
echo.
echo GENE EXPRESSION
echo ---------------
echo Not all genes are active at all times.
echo Gene regulation controls which proteins are made.
echo Promoters and repressors control gene expression.
) > Chapters\MolecularBiology.txt

:: ─── QUIZZES ───────────────────────────────────────────────────────────────

(
echo What does OOP stand for?
echo Object-Oriented Programming
echo Open Object Protocol
echo Operational Output Processing
echo Ordered Object Paradigm
echo A
echo Which OOP concept wraps data and functions together?
echo Polymorphism
echo Inheritance
echo Encapsulation
echo Abstraction
echo C
echo What does inheritance allow a subclass to do?
echo Delete parent methods
echo Acquire properties of a parent class
echo Override all parent constructors
echo Run faster than parent class
echo B
echo Which concept hides complex implementation details?
echo Encapsulation
echo Polymorphism
echo Abstraction
echo Inheritance
echo C
echo What is a pure virtual function used for?
echo Deleting objects
echo Creating abstract classes
echo Allocating memory
echo Overloading operators
echo B
) > Quizzes\OOP.txt

(
echo What is the full form of DNA?
echo Deoxyribonucleic Acid
echo Dual Nitrogen Arrangement
echo Dynamic Nucleotide Array
echo Dense Nuclear Acid
echo A
echo Who discovered the double helix structure of DNA?
echo Darwin and Mendel
echo Watson and Crick
echo Pasteur and Koch
echo Curie and Bohr
echo B
echo Adenine pairs with which base in DNA?
echo Cytosine
echo Guanine
echo Uracil
echo Thymine
echo D
echo What is the unit of heredity called?
echo Chromosome
echo Nucleus
echo Gene
echo Allele
echo C
echo Mendel's Law of Segregation states that?
echo Genes are linked on chromosomes
echo Alleles separate during gamete formation
echo Mutations occur at random
echo All traits are dominant
echo B
) > Quizzes\Genetics.txt

(
echo LIFO stands for?
echo Last In First Out
echo Linear Input File Output
echo Low Index First Output
echo Last Index First Order
echo A
echo Which data structure uses FIFO order?
echo Stack
echo Queue
echo Linked List
echo Binary Tree
echo B
echo What is the time complexity of accessing an array element by index?
echo O(n)
echo O(log n)
echo O(1)
echo O(n^2)
echo C
echo Which data structure connects nodes using pointers?
echo Array
echo Queue
echo Linked List
echo Matrix
echo C
echo Which operation is used to add an element to a stack?
echo Enqueue
echo Push
echo Insert
echo Append
echo B
) > Quizzes\DataStructures.txt

(
echo What is the primary function of enzymes?
echo Store genetic information
echo Provide structural support
echo Catalyze biochemical reactions
echo Transport oxygen in blood
echo C
echo Which biomolecule is the primary source of energy?
echo Lipids
echo Carbohydrates
echo Proteins
echo Nucleic Acids
echo B
echo What is the chemical formula of glucose?
echo C12H22O11
echo C6H12O6
echo CH4
echo H2O
echo B
echo What property do lipids have?
echo Hydrophilic
echo Hydrophobic
echo Positively charged
echo Negatively charged
echo B
echo What are proteins made of?
echo Nucleotides
echo Fatty acids
echo Amino acids
echo Glucose units
echo C
) > Quizzes\Biochemistry.txt

(
echo What is the Central Dogma of Molecular Biology?
echo DNA to Protein directly
echo DNA to RNA to Protein
echo RNA to DNA to Protein
echo Protein to RNA to DNA
echo B
echo What enzyme unwinds the DNA double helix during replication?
echo Polymerase
echo Ligase
echo Helicase
echo Primase
echo C
echo What is a mutation?
echo A new protein being synthesized
echo A change in the DNA sequence
echo A type of cell division
echo A form of gene expression
echo B
echo Where does transcription occur in eukaryotic cells?
echo Ribosome
echo Mitochondria
echo Nucleus
echo Cytoplasm
echo C
echo What reads the mRNA to synthesize a protein?
echo Nucleus
echo Helicase
echo Ribosome
echo Lysosome
echo C
) > Quizzes\MolecularBiology.txt

echo.
echo  All chapters and quizzes generated successfully!
