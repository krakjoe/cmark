--TEST--
CommonMark\Node cached read startLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->firstChild->startLine;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
