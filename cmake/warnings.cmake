function(ang_add_more_warnings COMPILE_OPTIONS)
    if(NOT ANG_MORE_WARNINGS)
        return()
    endif()

    # ang_process_flag_availability(ANG_FANALYZER_WNO_ANALYZER_MALLOC_LEAK
    #  "-fanalyzer -Wno-analyzer-malloc-leak" "")
    ang_process_flag_availability(ANG_WABSTRACT_VTABLE_INIT
        "-Wabstract-vtable-init" "")
    ang_process_flag_availability(ANG_WALLOCA "-Walloca" "")
    ang_process_flag_availability(ANG_WALLOC_ZERO "-Walloc-zero" "")
    ang_process_flag_availability(ANG_WANON_ENUM_ENUM_CONVERSION
        "-Wanon-enum-enum-conversion" "")
    ang_process_flag_availability(ANG_WASSIGN_ENUM "-Wassign-enum" "")
    ang_process_flag_availability(ANG_WAUTO_IMPORT "-Wauto-import" "")
    ang_process_flag_availability(ANG_WBITFIELD_ENUM_CONVERSION
        "-Wbitfield-enum-conversion" "")
    ang_process_flag_availability(ANG_WCOMMA "-Wcomma" "")
    ang_process_flag_availability(ANG_WCOMPLETION_HANDLER
        "-Wcompletion-handler" "")
    ang_process_flag_availability(ANG_WCOMPUOND_TOKEN_SPLIT_BY_SPACE
        "-Wcompound-token-split-by-space" "")
    ang_process_flag_availability(ANG_WCONDITIONAL_UNITIALIZED
        "-Wconditional-uninitialized" "")
    ang_process_flag_availability(ANG_WCUSTOM_ATOMIC_PROPERTIES
        "-Wcustom-atomic-properties" "")
    ang_process_flag_availability(ANG_WDELETE_NON_ABSTRACT_NON_VIRTUAL_DTOR
        "-Wdelete-non-abstract-non-virtual-dtor" "-Wdelete-non-virtual-dtor")
    ang_process_flag_availability(ANG_WDEPRECATED_COPY_WITH_USER_PROVIDED_COPY
        "-Wdeprecated-copy-with-user-provided-copy" "")
    ang_process_flag_availability(ANG_WDEPRECATED_COPY_WITH_USER_PROVIDED_DTOR
        "-Wdeprecated-copy-with-user-provided-dtor" "")
    ang_process_flag_availability(ANG_WDEPRECATED_DYNAMIC_EXCEPTION_SPEC
        "-Wdeprecated-dynamic-exception-spec" "")
    ang_process_flag_availability(ANG_WDEPRECATED_IMPLEMENTATIONS
        "-Wdeprecated-implementations" "")
    ang_process_flag_availability(ANG_WDEPRECATED_THIS_CAPTURE
        "-Wdeprecated-this-capture" "")
    ang_process_flag_availability(ANG_WDIRECT_IVAR_ACCESS
        "-Wdirect-ivar-access" "")
    ang_process_flag_availability(ANG_WDOCUMENTATION "-Wdocumentation" "")
    ang_process_flag_availability(ANG_WDOCUMENTATION_DEPRECATED_SYNC
        "-Wdocumentation-deprecated-sync" "")
    ang_process_flag_availability(ANG_WDOCUMENTATION_HTML
        "-Wdocumentation-html" "")
    ang_process_flag_availability(ANG_WDOCUMENTATION_UNKNOWN_COMMAND
        "-Wdocumentation-unknown-command" "")
    ang_process_flag_availability(ANG_WDOLLAR_IN_IDENTIFIER_EXTENSION
        "-Wdollar-in-identifier-extension" "")
    ang_process_flag_availability(ANG_WDUPLICATE_METHOD_ARG
        "-Wduplicate-method-arg" "")
    ang_process_flag_availability(ANG_WDUPLICATE_METHOD_MATCH
        "-Wduplicate-method-match" "")
    ang_process_flag_availability(ANG_WDUPLICATED_BRANCHES
        "-Wduplicated-branches" "")
    ang_process_flag_availability(ANG_WDUPLICATED_COND "-Wduplicated-cond"
        "")
    ang_process_flag_availability(ANG_WEMBEDDED_DIRECTIVE
        "-Wembedded-directive" "")
    ang_process_flag_availability(ANG_WEMPTY_INIT_STMT "-Wempty-init-stmt"
        "")
    ang_process_flag_availability(ANG_WEXIT_TIME_DESTRUCTORS
        "-Wexit-time-destructors" "")
    ang_process_flag_availability(ANG_WEXPLICIT_OWNERSHIP_TYPE
        "-Wexplicit-ownership-type" "")
    ang_process_flag_availability(ANG_WFIXED_ENUM_EXTENSION
        "-Wfixed-enum-extension" "")
    ang_process_flag_availability(ANG_WFORMAT_OVERFLOW_2
        "-Wformat-overflow=2" "")
    ang_process_flag_availability(ANG_WFORMAT_SIGNEDNESS
        "-Wformat-signedness" "")
    ang_process_flag_availability(ANG_WFORMAT_TYPE_CONFUSION
        "-Wformat-type-confusion" "")
    ang_process_flag_availability(ANG_WFOUR_CHAR_CONSTANTS
        "-Wfour-char-constants" "")
    ang_process_flag_availability(ANG_WGCC_COMPAT "-Wgcc-compat" "")
    ang_process_flag_availability(ANG_WGLOBAL_CONSTRUCTORS
        "-Wglobal-constructors" "")
    ang_process_flag_availability(ANG_WGNU_ANONYMOUS_STRUCT
        "-Wgnu-anonymous-struct" "")
    ang_process_flag_availability(ANG_WGNU_AUTO_TYPE "-Wgnu-auto-type" "")
    ang_process_flag_availability(ANG_WGNU_BINARY_LITERAL
        "-Wgnu-binary-literal" "")
    ang_process_flag_availability(ANG_WGNU_CASE_RANGE "-Wgnu-case-range"
        "")
    ang_process_flag_availability(ANG_WGNU_COMPOUND_LITERAL_INITIALIZER
        "-Wgnu-compound-literal-initializer" "")
    ang_process_flag_availability(ANG_WGNU_CONDITIONAL_OMITTED_OPERAND
        "-Wgnu-conditional-omitted-operand" "")
    ang_process_flag_availability(ANG_WGNU_DESIGNATOR "-Wgnu-designator"
        "")
    ang_process_flag_availability(ANG_WGNU_EMPTY_INITIALIZER
        "-Wgnu-empty-initializer" "")
    ang_process_flag_availability(ANG_WGNU_EMPTY_STRUCT
        "-Wgnu-empty-struct" "")
    ang_process_flag_availability(ANG_WGNU_FLEXIBLE_ARRAY_INITIALIZER
        "-Wgnu-flexible-array-initializer" "")
    ang_process_flag_availability(ANG_WGNU_FLEXIBLE_ARRAY_UNION_MEMBER
        "-Wgnu-flexible-array-union-member" "")
    ang_process_flag_availability(ANG_WGNU_FOLDING_CONSTANT
        "-Wgnu-folding-constant" "")
    ang_process_flag_availability(ANG_WGNU_IMAGINARY_CONSTANT
        "-Wgnu-imaginary-constant" "")
    ang_process_flag_availability(ANG_WGNU_INCLUDE_NEXT
        "-Wgnu-include-next" "")
    ang_process_flag_availability(ANG_WGNU_LABEL_AS_VALUE
        "-Wgnu-label-as-value" "")
    ang_process_flag_availability(ANG_WGNU_REDECLARED_ENUM
        "-Wgnu-redeclared-enum" "")
    ang_process_flag_availability(ANG_WGNU_STATEMENT_EXPRESSION
        "-Wgnu-statement-expression" "")
    ang_process_flag_availability(ANG_WGNU_UNION_CAST "-Wgnu-union-cast"
        "")
    ang_process_flag_availability(ANG_WGNU_ZERO_LINE_DIRECTIVE
        "-Wgnu-zero-line-directive" "")
    ang_process_flag_availability(ANG_WGNU_ZERO_VARIADIC_MACRO_ARGUMENTS
        "-Wgnu-zero-variadic-macro-arguments" "")
    ang_process_flag_availability(ANG_WHEADER_HYGIENE "-Wheader-hygiene" "")
    ang_process_flag_availability(ANG_WIDIOMATIC_PARENTHESES
        "-Widiomatic-parentheses" "")
    ang_process_flag_availability(ANG_WIF_NOT_ALIGNED "-Wif-not-aligned"
        "")
    ang_process_flag_availability(ANG_WIMPLICIT_FALLTHROUGH_5
        "-Wimplicit-fallthrough=5" "-Wimplicit-fallthrough")
    ang_process_flag_availability(
        ANG_WIMPORT_PREPROCESSOR_DIRECTIVE_PEDANTIC
        "-Wimport-preprocessor-directive-pedantic" "")
    ang_process_flag_availability(
        ANG_WINCONSISTENT_MISSING_DESTRUCTOR_OVERRIDE
        "-Winconsistent-missing-destructor-override" "")
    ang_process_flag_availability(ANG_WINFINITE_RECURSION
        "-Winfinite-recursion" "")
    ang_process_flag_availability(ANG_WINT_IN_BOOL_CONTEXT
        "-Wint-in-bool-context" "")
    ang_process_flag_availability(ANG_WINVALID_OR_NONEXISTENT_DIRECTORY
        "-Winvalid-or-nonexistent-directory" "")
    ang_process_flag_availability(ANG_WKEYWORD_MACRO "-Wkeyword-macro" "")
    ang_process_flag_availability(ANG_WLANGUAGE_EXTENSION_TOKEN
        "-Wlanguage-extension-token" "")
    ang_process_flag_availability(ANG_WLOGICAL_OP "-Wlogical-op" "")
    ang_process_flag_availability(ANG_WMAYBE_UNINITIALIZED
        "-Wmaybe-unitialized" "-Wsometimes-uninitialized")
    ang_process_flag_availability(ANG_WMICROSOFT_ANON_TAG
        "-Wmicrosoft-anon-tag" "")
    ang_process_flag_availability(ANG_WMICROSOFT_CHAR_SIZE
        "-Wmicrosoft-char-size" "")
    ang_process_flag_availability(ANG_WMICROSOFT_CHARIZE
        "-Wmicrosoft-charize" "")
    ang_process_flag_availability(ANG_WMICROSOFT_COMMENT_PASTE
        "-Wmicrosoft-comment-paste" "")
    ang_process_flag_availability(ANG_WMICROSOFT_CPP_MACRO
        "-Wmicrosoft-cpp-macro" "")
    ang_process_flag_availability(ANG_WMICROSOFT_ENUM_VALUE
        "-Wmicrosoft-enum-value" "")
    ang_process_flag_availability(ANG_WMICROSOFT_END_OF_FILE
        "-Wmicrosoft-end-of-file" "")
    ang_process_flag_availability(ANG_WMICROSOFT_ENUM_VALUE
        "-Wmicrosoft-enum-value" "")
    ang_process_flag_availability(ANG_WMICROSOFT_FIXED_ENUM
        "-Wmicrosoft-fixed-enum" "")
    ang_process_flag_availability(ANG_WMICROSOFT_FLEXIBLE_ARRAY
        "-Wmicrosoft-flexible-array" "")
    ang_process_flag_availability(ANG_WMICROSOFT_REDECLARE_STATIC
        "-Wmicrosoft-redeclare-static" "")
    ang_process_flag_availability(ANG_WMISMATCHED_TAGS "-Wmismatched-tags" "")
    ang_process_flag_availability(ANG_WMISSING_METHOD_RETURN_TYPE
        "-Wmissing-method-return-type" "")
    ang_process_flag_availability(ANG_WNESTED_ANON_TYPES
        "-Wnested-anon-types" "")
    ang_process_flag_availability(ANG_WNEWLINE_EOF "-Wnewline-eof" "")
    ang_process_flag_availability(ANG_WNONNULL_COMPARE "-Wnonnull-compare"
        "")
    ang_process_flag_availability(ANG_WNONPORTABLE_SYSTEM_INCLUDE_PATH
        "-Wnonportable-system-include-path" "")
    ang_process_flag_availability(ANG_WNOPACKED_BITFIELD_COMPAT
        "-Wnopacked-bitfield-compat" "")
    ang_process_flag_availability(ANG_WNULL_POINTER_ARITHMETIC
        "-Wnull-pointer-arithmetic" "")
    ang_process_flag_availability(ANG_WQUOTED_INCLUDE_IN_FRAMEWORK_HEADER
        "-Wquoted-include-in-framework-header" "")
    ang_process_flag_availability(ANG_WREDUNDANT_MOVE "-Wredundant-move"
        "")
    ang_process_flag_availability(ANG_WREORDER_CTOR "-Wreorder-ctor" "")
    ang_process_flag_availability(ANG_WREORDER "-Wreorder"
        "${ANG_WREORDER_CTOR}")
    ang_process_flag_availability(ANG_WRESERVED_ID_MACRO
        "-Wreserver-id-macro" "")
    ang_process_flag_availability(ANG_WRESERVED_IDENTIFIER
        "-Wreserved-identifier" "${ANG_WRESERVED_ID_MACRO}")
    ang_process_flag_availability(ANG_WSELF_ASSIGN_OVERLOADED
        "-Wself-assign-overloaded" "")
    ang_process_flag_availability(ANG_WSHADOW_FIELD_IN_CONSTRUCTOR_MODIFIED
        "-Wshadow-field-in-constructor-modified" "")
    ang_process_flag_availability(ANG_WSHIFT_OVERFLOW_2
        "-Wshift-overflow=2" "-Wshift-overflow;-Wshift-sign-overflow")
    ang_process_flag_availability(ANG_WSIGNED_ENUM_BITFIELD
        "-Wsigned-enum-bitfield" "")
    ang_process_flag_availability(ANG_WSTRING_CONCATENATION
        "-Wstring-concatenation" "")
    ang_process_flag_availability(ANG_WSTRINGOP_OVERFLOW_4
        "-Wstringop-overflow=4" "")
    # ang_process_flag_availability(ANG_WSTRINGOP_TRUNCATION
    #     "-Wstringop-truncation" "")
    ang_process_flag_availability(ANG_WSUGGEST_ATTRIBUTE_COLD
        "-Wsuggest-attribute=cold" "")
    ang_process_flag_availability(ANG_WSUGGEST_ATTRIBUTE_CONST
        "-Wsuggest-attribute=const" "")
    ang_process_flag_availability(ANG_WSUGGEST_ATTRIBUTE_FORMAT
        "-Wsuggest-attribute=format" "")
    ang_process_flag_availability(ANG_WSUGGEST_ATTRIBUTE_MALLOC
        "-Wsuggest-attribute=malloc" "")
    ang_process_flag_availability(ANG_WSUGGEST_ATTRIBUTE_NORETURN
        "-Wsuggest-attribute=noreturn" "")
    ang_process_flag_availability(ANG_WSUGGEST_ATTRIBUTE_PURE
        "-Wsuggest-attribute=pure" "")
    ang_process_flag_availability(ANG_WSUGGEST_DESTRUCTOR_OVERRIDE
        "-Wsuggest-destructor-override" "")
    ang_process_flag_availability(ANG_WSUPER_CLASS_METHOD_MISMATCH
        "-Wsuper-class-method-mismatch" "")
    ang_process_flag_availability(ANG_WTAUTOLOGICAL_TYPE_LIMIT_COMPARE
        "-Wtautological-type-limit-compare" "")
    ang_process_flag_availability(
        ANG_WTAUTOLOGICAL_UNSIGNED_ENUM_ZERO_COMPARE
        "-Wtautological-unsigned-enum-zero-compare" "")
    ang_process_flag_availability(ANG_WTAUTOLOGICAL_UNSIGNED_ZERO_COMPARE
        "-Wtautological-unsigned-zero-compare" "")
    ang_process_flag_availability(ANG_WTAUTOLOGICAL_VALUE_RANGE_COMPARE
        "-Wtautological-value-range-compare" "")
    ang_process_flag_availability(ANG_WTHREAD_SAFERY_ANALYSIS
        "-Wthread-safery-analysis" "")
    ang_process_flag_availability(ANG_WTHREAD_SAFERY_BETA
        "-Wthread-safery-beta" "")
    ang_process_flag_availability(ANG_WTHREAD_SAFERY_NEGATIVE
        "-Wthread-safery-negative" "")
    ang_process_flag_availability(ANG_WTHREAD_SAFERY_PRECISE
        "-Wthread-safery-precise" "")
    ang_process_flag_availability(ANG_WTHREAD_SAFERY_VERBOSE
        "-Wthread-safery-verbose" "")
    ang_process_flag_availability(ANG_WUNDEF_PREFIX "-Wundef-prefix" "")
    ang_process_flag_availability(ANG_WUNDEFINED_REINTERPRET_CAST
        "-Wundefined-reinterpret-cast" "")
    ang_process_flag_availability(ANG_WUNINITIALIZED_CONST_REFERENCE
        "-Wuninitialized-const-reference" "")
    ang_process_flag_availability(ANG_WUNNEEDED_INTERNAL_DECLARATION
        "-Wunneeded-internal-declaration" "")
    ang_process_flag_availability(ANG_WUNNEEDED_MEMBER_FUNCTION
        "-Wunneeded-member-function" "")
    ang_process_flag_availability(ANG_WUNREACHABLE_CODE_BREAK
        "-Wunreachable-code-break" "")
    ang_process_flag_availability(ANG_WUNREACHABLE_CODE_LOOP_INCREMENT
        "-Wunreachable-code-loop-increment" "")
    ang_process_flag_availability(ANG_WUNREACHABLE_CODE_RETURN
        "-Wunreachable-code-return" "")
    ang_process_flag_availability(ANG_WUNSAFE_LOOP_OPTIMIZATIONS
        "-Wunsafe-loop-optimizations" "")
    ang_process_flag_availability(ANG_WUNSUPPORTED_DLL_BASE_CLASS_TEMPLATE
        "-Wunsupported-dll-base-class-template" "")
    ang_process_flag_availability(ANG_WUNUSED_EXCEPTION_PARAMETER
        "-Wunused-exception-parameter" "")
    ang_process_flag_availability(ANG_WUNUSED_LAMBDA_CAPTURE
        "-Wunused-lambda-capture" "")
    ang_process_flag_availability(ANG_WUNUSED_PRIVATE_FIELD
        "-Wunused-private-field" "")
    ang_process_flag_availability(ANG_WUNUSED_PROPERTY_IVAR
        "-Wunused-property-ivar" "")
    ang_process_flag_availability(ANG_WUNUSED_TEMPLATE "-Wunused-template" "")
    ang_process_flag_availability(ANG_WUSED_BUT_MARKED_UNUSED
        "-Wused-but-marked-unused" "")
    ang_process_flag_availability(ANG_WVECTOR_OPERATION_PERFORMANCE
        "-Wvector-operation-performance" "")
    ang_process_flag_availability(ANG_WWEAK_TEMPLATE_VTABLES
        "-Wweak-template-vtables" "")
    ang_process_flag_availability(ANG_WWEAK_VTABLES "-Wweak-vtables" "")
    ang_process_flag_availability(ANG_WZERO_LENGTH_ARRAY
        "-Wzero-length-array" "")

    unset(ANG_WARNINGS)

    list(APPEND ANG_WARNINGS
        # https://stackoverflow.com/questions/64594953/stdvector-null-pointer-dereference-from-g-fanalyzer
        # ${ANG_FANALYZER_WNO_ANALYZER_MALLOC_LEAK}
        ${ANG_WALLOCA}
        ${ANG_WALLOC_ZERO}
        ${ANG_WANON_ENUM_ENUM_CONVERSION}
        ${ANG_WABSTRACT_VTABLE_INIT}
        ${ANG_WASSIGN_ENUM}
        ${ANG_WAUTO_IMPORT}
        ${ANG_WBITFIELD_ENUM_CONVERSION}
        -Wcast-qual
        ${ANG_WCOMMA}
        ${ANG_WCOMPLETION_HANDLER}
        ${ANG_WCOMPUOND_TOKEN_SPLIT_BY_SPACE}
        ${ANG_WCONDITIONAL_UNITIALIZED}
        -Wctor-dtor-privacy
        ${ANG_WCUSTOM_ATOMIC_PROPERTIES}
        -Wdangling-else
        ${ANG_WDELETE_NON_ABSTRACT_NON_VIRTUAL_DTOR}
        ${ANG_WDEPRECATED_COPY_WITH_USER_PROVIDED_COPY}
        ${ANG_WDEPRECATED_COPY_WITH_USER_PROVIDED_DTOR}
        ${ANG_WDEPRECATED_DYNAMIC_EXCEPTION_SPEC}
        ${ANG_WDEPRECATED_IMPLEMENTATIONS}
        ${ANG_WDEPRECATED_THIS_CAPTURE}
        ${ANG_WDIRECT_IVAR_ACCESS}
        -Wdisabled-optimization
        ${ANG_WDOCUMENTATION}
        ${ANG_WDOCUMENTATION_DEPRECATED_SYNC}
        ${ANG_WDOCUMENTATION_HTML}
        ${ANG_WDOCUMENTATION_UNKNOWN_COMMAND}
        ${ANG_WDOLLAR_IN_IDENTIFIER_EXTENSION}
        ${ANG_WDUPLICATE_METHOD_ARG}
        ${ANG_WDUPLICATE_METHOD_MATCH}
        ${ANG_WDUPLICATED_BRANCHES}
        ${ANG_WDUPLICATED_COND}
        # -Weffc++
        ${ANG_WEMBEDDED_DIRECTIVE}
        ${ANG_WEMPTY_INIT_STMT}
        ${ANG_WEXIT_TIME_DESTRUCTORS}
        ${ANG_WEXPLICIT_OWNERSHIP_TYPE}
        ${ANG_WFIXED_ENUM_EXTENSION}
        -Wformat
        ${ANG_WFORMAT_OVERFLOW_2}
        ${ANG_WFORMAT_SIGNEDNESS}
        ${ANG_WFORMAT_TYPE_CONFUSION}
        -Wformat-y2k
        ${ANG_WFOUR_CHAR_CONSTANTS}
        ${ANG_GCC_COMPAT}
        ${ANG_WGLOBAL_CONSTRUCTORS}
        ${ANG_WGNU_ANONYMOUS_STRUCT}
        ${ANG_WGNU_AUTO_TYPE}
        ${ANG_WGNU_BINARY_LITERAL}
        ${ANG_WGNU_CASE_RANGE}
        ${ANG_WGNU_COMPOUND_LITERAL_INITIALIZER}
        ${ANG_WGNU_CONDITIONAL_OMITTED_OPERAND}
        ${ANG_WGNU_DESIGNATOR}
        ${ANG_WGNU_EMPTY_INITIALIZER}
        ${ANG_WGNU_EMPTY_STRUCT}
        ${ANG_WGNU_FLEXIBLE_ARRAY_INITIALIZER}
        ${ANG_WGNU_FLEXIBLE_ARRAY_UNION_MEMBER}
        ${ANG_WGNU_FOLDING_CONSTANT}
        ${ANG_WGNU_IMAGINARY_CONSTANT}
        ${ANG_WGNU_INCLUDE_NEXT}
        ${ANG_WGNU_LABEL_AS_VALUE}
        ${ANG_WGNU_REDECLARED_ENUM}
        ${ANG_WGNU_STATEMENT_EXPRESSION}
        ${ANG_WGNU_UNION_CAST}
        ${ANG_WGNU_ZERO_LINE_DIRECTIVE}
        ${ANG_WGNU_ZERO_VARIADIC_MACRO_ARGUMENTS}
        ${ANG_WHEADER_HYGIENE}
        ${ANG_WIDIOMATIC_PARENTHESES}
        ${ANG_WIF_NOT_ALIGNED}
        -Wignored-qualifiers
        ${ANG_WINCONSISTENT_MISSING_DESTRUCTOR_OVERRIDE}
        -Winit-self
        -Winvalid-pch
        ${ANG_WIMPLICIT_FALLTHROUGH_5}
        ${ANG_WIMPORT_PREPROCESSOR_DIRECTIVE_PEDANTIC}
        ${ANG_WINFINITE_RECURSION}
        -Winline
        ${ANG_WINT_IN_BOOL_CONTEXT}
        ${ANG_WINVALID_OR_NONEXISTENT_DIRECTORY}
        ${ANG_WKEYWORD_MACRO}
        ${ANG_WLANGUAGE_EXTENSION_TOKEN}
        ${ANG_WLOGICAL_OP}
        -Wmain
        ${ANG_WMAYBE_UNITIALIZED}
        ${ANG_WMICROSOFT_ANON_TAG}
        ${ANG_WMICROSOFT_CHAR_SIZE}
        ${ANG_WMICROSOFT_CHARIZE}
        ${ANG_WMICROSOFT_COMMENT_PASTE}
        ${ANG_WMICROSOFT_CPP_MACRO}
        ${ANG_WMICROSOFT_END_OF_FILE}
        ${ANG_WMICROSOFT_ENUM_VALUE}
        ${ANG_WMICROSOFT_FIXED_ENUM}
        ${ANG_WMICROSOFT_FLEXIBLE_ARRAY}
        ${ANG_WMICROSOFT_REDECLARE_STATIC}
        ${ANG_WMISMATCHED_TAGS}
        -Wmissing-include-dirs
        ${ANG_WMISSING_METHOD_RETURN_TYPE}
        -Wmissing-noreturn
        ${ANG_WNESTED_ANON_TYPESNESTED}
        ${ANG_WNEWLINE_EOF}
        -Wnonnull
        ${ANG_WNONPORTABLE_SYSTEM_INCLUDE_PATH}
        -Wnoexcept
        ${ANG_WNONNULL_COMPARE}
        ${ANG_WNOPACKED_BITFIELD_COMPAT}
        -Wnon-virtual-dtor
        -Wnull-dereference
        ${ANG_WNULL_POINTER_ARITHMETIC}
        -Wold-style-cast
        -Woverlength-strings
        -Woverloaded-virtual
        -Wplacement-new=1
        -Wpointer-arith
        ${ANG_WQUOTED_INCLUDE_IN_FRAMEWORK_HEADER}
        -Wredundant-decls
        ${ANG_WREDUNDANT_MOVE}
        ${ANG_WREORDER}
        ${ANG_WRESERVED_IDENTIFIER}
        ${ANG_WSELF_ASSIGN_OVERLOADED}
        -Wsign-promo
        ${ANG_WSHADOW_FIELD_IN_CONSTRUCTOR_MODIFIED}
        ${ANG_WSHIFT_OVERFLOW_2}
        -Wsign-compare
        ${ANG_WSIGNED_ENUM_BITFIELD}
        -Wstrict-null-sentinel
        -Wstrict-overflow=4
        ${ANG_WSTRING_CONCATENATION}
        ${ANG_WSTRINGOP_OVERFLOW_4}
        # ${ANG_WSTRINGOP_TRUNCATION}
        ${ANG_WSUGGEST_ATTRIBUTE_COLD}
        ${ANG_WSUGGEST_ATTRIBUTE_CONST}
        ${ANG_WSUGGEST_ATTRIBUTE_FORMAT}
        ${ANG_WSUGGEST_ATTRIBUTE_MALLOC}
        ${ANG_WSUGGEST_ATTRIBUTE_NORETURN}
        ${ANG_WSUGGEST_ATTRIBUTE_PURE}
        ${ANG_WSUGGEST_DESTRUCTOR_OVERRIDE}
        -Wsuggest-final-methods
        -Wsuggest-final-types
        -Wsuggest-override
        ${ANG_WSUPER_CLASS_METHOD_MISMATCH}
        -Wswitch-default
        -Wswitch-enum
        -Wtautological-compare
        ${ANG_WTAUTOLOGICAL_TYPE_LIMIT_COMPARE}
        ${ANG_WTAUTOLOGICAL_UNSIGNED_ENUM_ZERO_COMPARE}
        ${ANG_WTAUTOLOGICAL_UNSIGNED_ZERO_COMPARE}
        ${ANG_WTAUTOLOGICAL_VALUE_RANGE_COMPARE}
        ${ANG_WTHREAD_SAFERY_ANALYSIS}
        ${ANG_WTHREAD_SAFERY_BETA}
        ${ANG_WTHREAD_SAFERY_NEGATIVE}
        ${ANG_WTHREAD_SAFERY_PRECISE}
        ${ANG_WTHREAD_SAFERY_VERBOSE}
        -Wundef
        ${ANG_WUNDEF_PREFIX}
        ${ANG_WUNDEFINED_REINTERPRET_CAST}
        -Wuninitialized
        ${ANG_WUNINITIALIZED_CONST_REFERENCE}
        -Wunknown-pragmas
        ${ANG_WUNNEEDED_INTERNAL_DECLARATION}
        ${ANG_WUNNEEDED_MEMBER_FUNCTION}
        ${ANG_WUNREACHABLE_CODE_BREAK}
        ${ANG_WUNREACHABLE_CODE_LOOP_INCREMENT}
        ${ANG_WUNREACHABLE_CODE_RETURN}
        ${ANG_WUNSAFE_LOOP_OPTIMIZATIONS}
        ${ANG_WUNSUPPORTED_DLL_BASE_CLASS_TEMPLATE}
        -Wunused-but-set-variable
        ${ANG_WUNUSED_EXCEPTION_PARAMETER}
        -Wunused-label
        ${ANG_WUNUSED_LAMBDA_CAPTURE}
        -Wunused-local-typedefs
        ${ANG_WUNUSED_PRIVATE_FIELD}
        ${ANG_WUNUSED_PROPERTY_IVAR}
        ${ANG_WUNUSED_TEMPLATE}
        ${ANG_WUSED_BUT_MARKED_UNUSED}
        -Wuseless-cast
        ${ANG_WVECTOR_OPERATION_PERFORMANCE}
        ${ANG_WWEAK_TEMPLATE_VTABLES}
        ${ANG_WWEAK_VTABLES}
        -Wwrite-strings
        -Wzero-as-null-pointer-constant
        ${ANG_WZERO_LENGTH_ARRAY}
    )
    set(
        ${COMPILE_OPTIONS}
        "${${COMPILE_OPTIONS}};${ANG_WARNINGS}"
        PARENT_SCOPE
    )
endfunction()
