--TEST--
CommonMark\Render Latex Width
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
hello world
EOD
);

echo CommonMark\Render\Latex($doc, CommonMark\Render\Normal, 4);
?>
--EXPECT--
hello
world

