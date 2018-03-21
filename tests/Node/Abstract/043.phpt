--TEST--
CommonMark\Node cached read endColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->firstChild->endColumn;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
