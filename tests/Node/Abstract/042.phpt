--TEST--
CommonMark\Node cached read startColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->firstChild->startColumn;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
