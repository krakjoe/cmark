--TEST--
CommonMark\Node cached read endLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->firstChild->endLine;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
